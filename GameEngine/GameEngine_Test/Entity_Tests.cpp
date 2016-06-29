#include "gtest/gtest.h"
#include "Entity.h"

TEST(testEntity, entityInitTest) {
	Entity *entity = new Entity();
	ASSERT_TRUE(true);
	delete entity;
}

TEST(testEntity, entityDefaultParamTest) {
	Entity *entity = new Entity();
	EXPECT_FLOAT_EQ(entity->x, 0.f);
	EXPECT_FLOAT_EQ(entity->y, 0.f);
	EXPECT_FLOAT_EQ(entity->dx, 0.f);
	EXPECT_FLOAT_EQ(entity->dy, 0.f);
	EXPECT_EQ(entity->getDrawableType(), 1);
	EXPECT_EQ(entity->life, 100);
	EXPECT_EQ(entity->maxLife, 100);
	EXPECT_EQ(entity->direction, EAST);
	EXPECT_FALSE(entity->invulnerable);
	EXPECT_TRUE(entity->isVisible());
	delete entity;
}

TEST(testEntity, entityDmgTest) {
	Entity *entity = new Entity();
	entity->damage(10);
	EXPECT_EQ(entity->life, 90);
	entity->damage(81);
	EXPECT_EQ(entity->life, 9);
	entity->damage(100);
	EXPECT_EQ(entity->life, 0);
	delete entity;
}

TEST(testEntity, entityRecoverTest) {
	Entity *entity = new Entity();
	entity->damage(81);
	entity->recover(1);
	EXPECT_EQ(entity->life, 20);
	entity->recover(79);
	EXPECT_EQ(entity->life, 99);
	entity->recover(100);
	EXPECT_EQ(entity->life, 100);
	delete entity;
}

TEST(testEntity, entityMovementTest) {
	Entity *entity = new Entity();
	entity->dx = 2.f;
	for (int i = 0; i < 10; i++) // Simulate updatePosition()
		entity->updatePosition(Vector2f(entity->dx, entity->dy));
	EXPECT_FLOAT_EQ(entity->x, 20.f);
	entity->dx = -2.f;
	entity->dy = 5.f;
	entity->updatePosition(Vector2f(entity->dx, entity->dy));
	EXPECT_FLOAT_EQ(entity->x, 18.f);
	EXPECT_FLOAT_EQ(entity->y, 5.f);
	delete entity;
}

TEST(testEntity, entityCollisionTest) {
	Entity *a = new Entity();
	Entity *b = new Entity();
	Vector2f overlap = Vector2f(0.f, 0.f);

	a->cWidth = 100;
	a->cHeight = 100;
	b->cWidth = 100;
	b->cHeight = 80;

	a->updatePosition(Vector2f(150, 120));
	b->updatePosition(Vector2f(100, 0));
	EXPECT_FALSE(a->insideCollidable(b));
	
	// ENTITY OVERLAP TESTS
	if (a->insideCollidable(b))
		overlap = a->getEntityOverlap(b);
	EXPECT_FLOAT_EQ(overlap.x, 0.f);
	EXPECT_FLOAT_EQ(overlap.y, 0.f);

	b->updatePosition(Vector2f(50, 50));

	if (a->insideCollidable(b))
		overlap = a->getEntityOverlap(b);
	EXPECT_FLOAT_EQ(overlap.x, 0.f);
	EXPECT_FLOAT_EQ(overlap.y, 1.f);
	
	// STATIC OVERLAP TESTS
	overlap = a->getStaticOverlap(b);
	EXPECT_FLOAT_EQ(overlap.x, 0.f);
	EXPECT_FLOAT_EQ(overlap.y, 21.f);

	b->updatePosition(Vector2f(90, 0));
	overlap = a->getStaticOverlap(b);
	EXPECT_FLOAT_EQ(overlap.x, -11.f);
	EXPECT_FLOAT_EQ(overlap.y, 0.f);

	b->updatePosition(Vector2f(-180, 39));
	overlap = a->getStaticOverlap(b);
	EXPECT_FLOAT_EQ(overlap.x, 11.f);
	EXPECT_FLOAT_EQ(overlap.y, 0.f);

	delete a;
	delete b;
}
