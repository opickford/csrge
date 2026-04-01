#include <engine/core/engine.h>

#include <engine/core/globals.h>
#include <engine/core/canvas.h>
#include <engine/core/transform.h>

#include <engine/utils/common.h>

#include <engine/maths/vector3.h>
#include <engine/common/status.h>

#include <engine/scripts/gameplay/player_controller.h>
#include <engine/scripts/rendering/billboard.h>

float* directions;

MeshBaseId sphere_base;
MeshBaseId cube_base;
MeshBaseId map_base;
MeshBaseId monkey_base;
MeshBaseId bowl_base;
MeshBaseId terrain_base;

CECS_EntityId map_entity;
CECS_EntityId monkey_entity;
CECS_EntityId player_entity;
CECS_EntityId billboard_entity;

void create_map(Engine* engine)
{
    resources_load_texture(&engine->resources, "C:/Users/olive/source/repos/csrge/res/textures/landscape.bmp");
    resources_load_texture(&engine->resources, "C:/Users/olive/source/repos/csrge/res/textures/fortnite_peter.bmp");
    resources_load_texture(&engine->resources, "C:/Users/olive/source/repos/csrge/res/textures/rickreal.bmp");
    
    // TODO: Map like a csgo 1v1 map, just a floor and scoreboard and maybe some obstacles.
    
    // TODO: Also for models, the scene could be global? I think MBs should be 
    //       global?
    Scene* scene = &engine->scene;
    Status status = scene_init(scene);
    
    // Load some mesh bases.
    sphere_base = mesh_bases_add(&scene->mesh_bases);
    mesh_base_from_obj(&scene->mesh_bases.bases[sphere_base], "C:/Users/olive/source/repos/csrge/res/models/sphere.obj");

    cube_base = mesh_bases_add(&scene->mesh_bases);
    mesh_base_from_obj(&scene->mesh_bases.bases[cube_base], "C:/Users/olive/source/repos/csrge/res/models/cube.obj");

    map_base = mesh_bases_add(&scene->mesh_bases);
    mesh_base_from_obj(&scene->mesh_bases.bases[map_base], "C:/Users/olive/source/repos/csrge/res/models/physics_test_map.obj");

    monkey_base = mesh_bases_add(&scene->mesh_bases);
    mesh_base_from_obj(&scene->mesh_bases.bases[monkey_base], "C:/Users/olive/source/repos/csrge/res/models/suzanne.obj");

    bowl_base = mesh_bases_add(&scene->mesh_bases);
    mesh_base_from_obj(&scene->mesh_bases.bases[bowl_base], "C:/Users/olive/source/repos/csrge/res/models/bowl.obj");

    terrain_base = mesh_bases_add(&scene->mesh_bases);
    mesh_base_from_obj(&scene->mesh_bases.bases[terrain_base], "C:/Users/olive/source/repos/csrge/res/models/terrain.obj");

    // Create terrain
    {
        CECS_EntityId cube_entity = cecs_create_entity(engine->ecs);
        map_entity = cube_entity;

        // Add a MeshInstance component.
        MeshInstance* mi = cecs_add_component(engine->ecs, cube_entity, COMPONENT_MESH_INSTANCE);
        mesh_instance_init(mi, &scene->mesh_bases.bases[terrain_base]);

        mi->texture_id = 0;

        {
            Transform* transform = cecs_add_component(engine->ecs, cube_entity, COMPONENT_TRANSFORM);
            transform_init(transform);
            transform->scale = v3_uniform(10);
        }
        
        // TODO: currently testing with static.
        //PhysicsData* physics_data = cecs_add_component(engine->ecs, cube_entity, COMPONENT_PHYSICS_DATA);
        //physics_data_init(physics_data);
        //physics_data->force = (V3){ 0,0,1 };

        Collider* collider = cecs_add_component(engine->ecs, cube_entity, COMPONENT_COLLIDER);
        collider_init(collider);

        collider->shape.type = COLLISION_SHAPE_MESH;

        //PhysicsData* pd = cecs_add_component(engine->ecs, cube_entity, COMPONENT_PHYSICS_DATA);
        //physics_data_init(pd);
        //pd->mass = 0.f; // TODO: TEMP: Isn't moved by other things?
        //pd->floating = 1;
    }

    // Create player
    {
        player_entity = cecs_create_entity(engine->ecs);

        // Add a MeshInstance component.
        MeshInstance* mi = cecs_add_component(engine->ecs, player_entity, COMPONENT_MESH_INSTANCE);
        mesh_instance_init(mi, &scene->mesh_bases.bases[sphere_base]);

        mi->texture_id = 1;

        {
            Transform* transform = cecs_add_component(engine->ecs, player_entity, COMPONENT_TRANSFORM);
            transform_init(transform);
            transform->scale = (V3) { 1, 2, 1 };
            transform->position = (V3) { 0, 3, 0 };
        }

        Collider* collider = cecs_add_component(engine->ecs, player_entity, COMPONENT_COLLIDER);
        collider_init(collider);

        collider->shape.type = COLLISION_SHAPE_ELLIPSOID;
        collider->shape.ellipsoid = (V3){ 1,2,1 };

        PhysicsData* pd = cecs_add_component(engine->ecs, player_entity, COMPONENT_PHYSICS_DATA);
        physics_data_init(pd);
        pd->mass = 50.f;
    }

    // Create billboard
    {
        billboard_entity = cecs_create_entity(engine->ecs);

        // Add a MeshInstance component.
        MeshInstance* mi = cecs_add_component(engine->ecs, billboard_entity, COMPONENT_MESH_INSTANCE);
        mesh_instance_init(mi, &scene->mesh_bases.bases[cube_base]);

        mi->texture_id = 2;

        {
            Transform* transform = cecs_add_component(engine->ecs, billboard_entity, COMPONENT_TRANSFORM);
            transform_init(transform);
            transform->scale = (V3){ 1, 2, 0 };
            transform->position = (V3){ 5, 3, 0 };
        }

       
        Collider* collider = cecs_add_component(engine->ecs, billboard_entity, COMPONENT_COLLIDER);
        collider_init(collider);

        //collider->shape.type = COLLISION_SHAPE_ELLIPSOID;
        //collider->shape.ellipsoid = (V3){ 1,2,1 };

        collider->shape.type = COLLISION_SHAPE_MESH;

        /*
        PhysicsData* pd = cecs_add_component(engine->ecs, billboard_entity, COMPONENT_PHYSICS_DATA);
        physics_data_init(pd);
        pd->mass = 50.f;*/
    }
    
    // MONKEY
    /*
    {
        CECS_EntityId cube_entity = cecs_create_entity(engine->ecs);
        monkey_entity = cube_entity;

        // Add a MeshInstance component.
        MeshInstance* mi = cecs_add_component(engine->ecs, cube_entity, COMPONENT_MESH_INSTANCE);
        mesh_instance_init(mi, &scene->mesh_bases.bases[monkey_base]);

        mi->texture_id = 0;

        Transform* transform = cecs_add_component(engine->ecs, cube_entity, COMPONENT_TRANSFORM);
        transform_init(transform);
        transform->scale = v3_uniform(1);

        // TODO: currently testing with static.
        //PhysicsData* physics_data = cecs_add_component(engine->ecs, cube_entity, COMPONENT_PHYSICS_DATA);
        //physics_data_init(physics_data);
        //physics_data->force = (V3){ 0,0,1 };

        Collider* collider = cecs_add_component(engine->ecs, cube_entity, COMPONENT_COLLIDER);
        collider_init(collider);

        collider->shape.type = COLLISION_SHAPE_MESH;
        //collider->shape.ellipsoid = v3_uniform(1.f);

        PhysicsData* pd = cecs_add_component(engine->ecs, cube_entity, COMPONENT_PHYSICS_DATA);
        physics_data_init(pd);
    }*/
  

    /*
    // TODO: TEMP: Currently setting the spawned cube to have an ellipsoid collider, but this is just for the 
    //             broad phase which is using the sphere.
    // Normally to calculate bounding sphere of square we would half the scale, however,
    // the input .obj goes from -1 to 1, so the length is 2.
    V3 half_sqrd = v3_mul_v3(transform->scale, transform->scale);
    float radius = sqrtf(half_sqrd.x + half_sqrd.y + half_sqrd.z);
    collider->shape.ellipsoid = v3_uniform(radius);
    printf("%f\n", radius);
    */
    scene->ambient_light = v3_uniform(1.f);
    //scene->ambient_light = v3_uniform(0.1f);
    
    scene->bg_colour = 0x11111111;
    
    // TODO: Should the camera be part of the scene??
    engine->renderer.camera.position = (V3) { 0, 0, 10.f };
}

void engine_on_init(Engine* engine)
{
    // TODO: Should really be init by the engine!!!
    g_draw_normals = 0;
    g_debug_shadows = 0;
    g_debug_velocities = 0;

    create_map(engine);
}

void engine_before_physics(Engine* engine, float dt)
{
    {
        PhysicsData* pd = cecs_get_component(engine->ecs, map_entity, COMPONENT_PHYSICS_DATA);
        //pd->velocity = (V3){ 0.f, 0.f, -1.f };
    }

    {
        PhysicsData* pd = cecs_get_component(engine->ecs, player_entity, COMPONENT_PHYSICS_DATA);
        Transform* t = cecs_get_component(engine->ecs, player_entity, COMPONENT_TRANSFORM);

        V3 dir = v3_normalised(v3_sub_v3(engine->renderer.camera.position, t->position));
        
        //v3_add_eq_v3(&pd->impulses, v3_mul_f(dir, 0.01));

    }

    player_controller_physics(engine, player_entity, dt);
    update_billboard(engine, billboard_entity, dt);
}

void engine_after_physics(Engine* engine, float physics_alpha)
{
    player_controller_camera(engine, player_entity);
}

void engine_on_keyup(Engine* engine, WPARAM wParam)
{
    switch (wParam)
    {
    case VK_F1:
    {
        MeshBaseId mb_ids[2] = { cube_base, sphere_base };

        MeshBaseId mb_id = mb_ids[(int)(random_float() + 0.5f)];

        Scene* scene = &engine->scene;

        V3 colour =
        {
            random_float(),
            random_float(),
            random_float()
        };

        
        const Camera* camera = &engine->renderer.camera;

        const V3 pos = v3_add_v3(camera->position, v3_mul_f(camera->direction, 10.f * (random_float() + 1)));

        CECS_EntityId cube_entity = cecs_create_entity(engine->ecs);
        MeshInstance* mi = cecs_add_component(engine->ecs, cube_entity, COMPONENT_MESH_INSTANCE);
        mesh_instance_init(mi, &scene->mesh_bases.bases[sphere_base]);
        mesh_instance_set_albedo(mi, &scene->mesh_bases.bases[sphere_base], colour);

        Transform* transform = cecs_add_component(engine->ecs, cube_entity, COMPONENT_TRANSFORM);
        transform_init(transform);
        transform->position = pos;

        break;
    }
    case VK_F2:
    {
        //g_draw_normals = !g_draw_normals;
        Scene* scene = &engine->scene;
        
        break;
    }
    case VK_F3:
    {
        V3 colour =
        {
            random_float(),
            random_float(),
            random_float()
        };
        
        // TODO: Should camera be an entity component or entity or leave it? Not sure.
        //       Fine for now.
        Camera* camera = &engine->renderer.camera;
        
        const V3 pos = v3_add_v3(camera->position, v3_mul_f(camera->direction, 10.f * (random_float() + 1)));

        CECS_EntityId e = cecs_create_entity(engine->ecs);
        PointLight* pl = cecs_add_component(engine->ecs, e, COMPONENT_POINT_LIGHT);
        pl->position = pos;
        pl->colour = colour;
        pl->strength = 1.f;

        break;
    }
    case VK_F4:
    {
        MeshInstance* mi = cecs_get_component(engine->ecs, 0, COMPONENT_MESH_INSTANCE);
        mesh_instance_destroy(mi);
        cecs_remove_component(engine->ecs, 0, COMPONENT_MESH_INSTANCE);

        cecs_destroy_entity(engine->ecs, 0);

        break;
    }
    case VK_F5:
    {   

        break;
    }
    case VK_F6:
    {
        g_debug_velocities = !g_debug_velocities;
        break;
    }
    case VK_F7:
    {
        CECS_EntityId cube_entity = cecs_create_entity(engine->ecs);
        map_entity = cube_entity;

        // Add a MeshInstance component.
        MeshInstance* mi = cecs_add_component(engine->ecs, cube_entity, COMPONENT_MESH_INSTANCE);
        mesh_instance_init(mi, &engine->scene.mesh_bases.bases[sphere_base]);

        Transform* transform = cecs_add_component(engine->ecs, cube_entity, COMPONENT_TRANSFORM);
        transform_init(transform);
        transform->scale = v3_uniform(3);
        transform->position = (V3){ 0, 10, 0 };

        Collider* collider = cecs_add_component(engine->ecs, cube_entity, COMPONENT_COLLIDER);
        collider_init(collider);

        collider->shape.type = COLLISION_SHAPE_ELLIPSOID;
        collider->shape.ellipsoid = transform->scale;


        PhysicsData* pd = cecs_add_component(engine->ecs, cube_entity, COMPONENT_PHYSICS_DATA);
        physics_data_init(pd);
        pd->mass = 100.f;

        break;
    }
    case VK_F8:
    {
        for (int i = 0; i < 10; ++i)
        {
            CECS_EntityId cube_entity = cecs_create_entity(engine->ecs);
            map_entity = cube_entity;

            // Add a MeshInstance component.
            MeshInstance* mi = cecs_add_component(engine->ecs, cube_entity, COMPONENT_MESH_INSTANCE);
            mesh_instance_init(mi, &engine->scene.mesh_bases.bases[sphere_base]);

            V3 colour =
            {
                random_float(),
                random_float(),
                random_float()
            };

            float size = random_float();

            mesh_instance_set_albedo(mi, &engine->scene.mesh_bases.bases[sphere_base], colour);

            Transform* transform = cecs_add_component(engine->ecs, cube_entity, COMPONENT_TRANSFORM);
            transform_init(transform);
            transform->scale = v3_uniform(size);
            transform->position = (V3) { 0, transform->scale.x + i * (transform->scale.x * 2), 0 };

            Collider* collider = cecs_add_component(engine->ecs, cube_entity, COMPONENT_COLLIDER);
            collider_init(collider);

            collider->shape.type = COLLISION_SHAPE_ELLIPSOID;
            collider->shape.ellipsoid = transform->scale;

            PhysicsData* pd = cecs_add_component(engine->ecs, cube_entity, COMPONENT_PHYSICS_DATA);
            physics_data_init(pd);
            pd->mass = 1.f;
        }
        
        break;
    }
    case 'H':
    {
        third_person = !third_person;
        break;
    }
    
    }
}

void engine_on_lmbdown(Engine* engine)
{
    Scene* scene = &engine->scene;

    // Create an entity
    CECS_EntityId cube_entity = cecs_create_entity(engine->ecs);

    //MeshBase* mb = &scene->mesh_bases.bases[cube_base];
    MeshBase* mb = &scene->mesh_bases.bases[sphere_base];

    // Add a MeshInstance component.
    cecs_add_component(engine->ecs, cube_entity, COMPONENT_MESH_INSTANCE);
    MeshInstance* mi = cecs_get_component(engine->ecs, cube_entity,
        COMPONENT_MESH_INSTANCE);
    mesh_instance_init(mi, mb);


    V3 colour =
    {
        random_float(),
        random_float(),
        random_float()
    };
    mesh_instance_set_albedo(mi, mb, colour);

    cecs_add_component(engine->ecs, cube_entity, COMPONENT_TRANSFORM);

    Transform* transform = cecs_get_component(engine->ecs, cube_entity, COMPONENT_TRANSFORM);
    transform_init(transform);
    transform->position = v3_add_v3(engine->renderer.camera.position, v3_mul_f(engine->renderer.camera.direction, 3));
    transform->scale = v3_uniform(0.1f);


    //transform->scale = v3_uniform(0.1);
    //transform->scale = (V3){ 0.5f,2,1 };

    PhysicsData* physics_data = cecs_add_component(engine->ecs, cube_entity, COMPONENT_PHYSICS_DATA);
    physics_data_init(physics_data);

    physics_data->mass = 1.f;

    // TODO: Dt?
    float speed = physics_data->mass * 20.f;
    v3_add_eq_v3(&physics_data->impulses, v3_mul_f(engine->renderer.camera.direction, speed));

    // TODO: Must remember that the pointers go invalid qUIck, should specifiy this in cecs!!!!

    Collider* collider = cecs_add_component(engine->ecs, cube_entity, COMPONENT_COLLIDER);
    collider_init(collider);
    collider->shape.ellipsoid = transform->scale;
}

int main()
{
	Engine engine;
	if (STATUS_OK == engine_init(&engine, 800, 600))
	{
		engine_run(&engine);
	}
	
	engine_destroy(&engine);

	return 0;
}
