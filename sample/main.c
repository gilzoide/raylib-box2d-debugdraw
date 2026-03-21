#include <raylib.h>
#include <box2d/box2d.h>
#include <raylib_box2d_debugdraw.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define PHYSICS_FPS 60

int main() {
	SetConfigFlags(FLAG_VSYNC_HINT);
	InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Raylib + Box2D debug draw");

	// World
	b2WorldDef world_def = b2DefaultWorldDef();
	world_def.gravity.y = 50;
	b2WorldId world = b2CreateWorld(&world_def);

	// Floor segment
	b2BodyDef floor_body_def = b2DefaultBodyDef();
	floor_body_def.type = b2_staticBody;
	floor_body_def.position = (b2Vec2){ 0, WINDOW_HEIGHT - 30 };
	floor_body_def.name = "floor";
	b2BodyId floor_body = b2CreateBody(world, &floor_body_def);
	b2Segment floor_segment = {
		{ 0, 0 },
		{ WINDOW_WIDTH, 0 },
	};
	b2ShapeDef floor_shape_def = b2DefaultShapeDef();
	b2ShapeId floor_shape = b2CreateSegmentShape(floor_body, &floor_shape_def, &floor_segment);

	// Box (polygon)
	b2BodyDef box_body_def = b2DefaultBodyDef();
	box_body_def.type = b2_dynamicBody;
	box_body_def.position = (b2Vec2){ WINDOW_WIDTH * 0.2, 100 };
	box_body_def.rotation = b2MakeRot(PI / 3);
	box_body_def.name = "box";
	b2BodyId box_body = b2CreateBody(world, &box_body_def);
	b2Polygon box_poly = b2MakeBox(25, 25);
	b2ShapeDef box_shape_def = b2DefaultShapeDef();
	b2ShapeId box_shape = b2CreatePolygonShape(box_body, &box_shape_def, &box_poly);

	// Rounded box (polygon)
	b2BodyDef rounded_box_body_def = b2DefaultBodyDef();
	rounded_box_body_def.type = b2_dynamicBody;
	rounded_box_body_def.position = (b2Vec2){ WINDOW_WIDTH * 0.4, 100 };
	rounded_box_body_def.rotation = b2MakeRot(PI / 3);
	rounded_box_body_def.name = "rounded_box";
	b2BodyId rounded_box_body = b2CreateBody(world, &rounded_box_body_def);
	b2Polygon rounded_box_poly = b2MakeRoundedBox(20, 20, 10);
	b2ShapeDef rounded_box_shape_def = b2DefaultShapeDef();
	b2ShapeId rounded_box_shape = b2CreatePolygonShape(rounded_box_body, &rounded_box_shape_def, &rounded_box_poly);

	// Ball (circle)
	b2BodyDef ball_body_def = b2DefaultBodyDef();
	ball_body_def.type = b2_dynamicBody;
	ball_body_def.position = (b2Vec2){ WINDOW_WIDTH * 0.6, 100 };
	ball_body_def.name = "ball";
	b2BodyId ball_body = b2CreateBody(world, &ball_body_def);
	b2Circle ball_circle = {
		{ 0, 0 },
		25,
	};
	b2ShapeDef ball_shape_def = b2DefaultShapeDef();
	ball_shape_def.density = 10;
	b2ShapeId ball_shape = b2CreateCircleShape(ball_body, &ball_shape_def, &ball_circle);

	// Capsule
	b2BodyDef capsule_body_def = b2DefaultBodyDef();
	capsule_body_def.type = b2_dynamicBody;
	capsule_body_def.position = (b2Vec2){ WINDOW_WIDTH * 0.8, 100 };
	capsule_body_def.name = "capsule";
	b2BodyId capsule_body = b2CreateBody(world, &capsule_body_def);
	b2Capsule capsule_circle = {
		{ 0, -10 },
		{ 5, 10 },
		15,
	};
	b2ShapeDef capsule_shape_def = b2DefaultShapeDef();
	capsule_shape_def.density = 10;
	b2ShapeId capsule_shape = b2CreateCapsuleShape(capsule_body, &capsule_shape_def, &capsule_circle);

	// Debug draw configuration
	b2DebugDraw debug_draw = b2RaylibDebugDraw();
	debug_draw.drawBodyNames = true;
	debug_draw.drawShapes = true;
	debug_draw.drawBounds = true;
	debug_draw.drawContacts = true;

	bool is_paused = false;
	while (!WindowShouldClose()) {
		// UPDATE
		if (IsKeyPressed(KEY_P)) {
			is_paused = !is_paused;
		}

		if (!is_paused) {
			b2World_Step(world, 1.0 / PHYSICS_FPS, 4);
		}

		// DRAW
		BeginDrawing();
			ClearBackground(RAYWHITE);
			DrawText("Press P to pause simulation", 2, 2, 16, BLACK);
			b2World_Draw(world, &debug_draw);
		EndDrawing();
	}
	CloseWindow();

	return 0;
}
