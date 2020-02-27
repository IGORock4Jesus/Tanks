#include "pch.h"
#include "CppUnitTest.h"
#include <EntityManager.h>
#include <InvalidCallException.h>
#include <ArgumentException.h>
#include <ArgumentNullException.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ECS::Tests
{
TEST_CLASS(EntityManagerTests)
{
public:
	// Create
	TEST_METHOD(Create_TryCreateWithZeroBuffer)
	{
		Assert::ExpectException<InvalidCallException>([]() {
			EntityManager manager{ 0 };
			Entity* entity = manager.Create();
			});
	}
	TEST_METHOD(Create_TryCreateWithZeroBuffer2)
	{
		Assert::ExpectException<InvalidCallException>([]() {
			EntityManager manager{ 1 };
			Entity* entity = manager.Create();
			entity = manager.Create();
			});
	}
	TEST_METHOD(Create_CreateNormal) {
		EntityManager manager{ 1 };
		Entity* entity = manager.Create();
		Assert::IsNotNull(entity);
		Assert::AreEqual(1ULL, manager.Count());
	}
	// Remove
	TEST_METHOD(Remove_NullArgument) {
		Assert::ExpectException<ArgumentNullException>([]() {
			EntityManager manager{ 1 };
			manager.Remove(nullptr);
			});
	}
	TEST_METHOD(Remove_UnknonEntity) {
		Assert::ExpectException<ArgumentExcpection>([]() {
			EntityManager manager{ 1 };
			Entity entity;
			manager.Remove(&entity);
			});
	}
	TEST_METHOD(Remove_Normal) {
		EntityManager manager{ 1 };
		Entity* entity = manager.Create();
		manager.Remove(entity);
		Assert::AreEqual(0ULL, manager.Count());
	}
	// Get
	TEST_METHOD(Get_Unknown) {
		EntityManager manager{ 1 };
		const Entity* entity = manager.Get(L"test");
		Assert::IsNull(entity);
	}
	TEST_METHOD(Get_Normal) {
		EntityManager manager{ 1 };
		Entity* test = manager.Create();
		test->name = L"test";
		const Entity* entity = manager.Get(L"test");
		Assert::IsNotNull(entity);
	}
};
}