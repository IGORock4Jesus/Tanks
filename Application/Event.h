#pragma once

#include <memory>
#include <list>

template <typename... TArgs>
class Event {
	enum class DelegateType
	{
		Static, Objective
	};

	class Delegate
	{
		DelegateType type;
	public:
		Delegate(DelegateType type)
			: type{ type } {}
		DelegateType GetType()const { return type; }
		virtual void Process(TArgs... args) = 0;
	};
	
	template <typename TFunction>
	class StaticDelegate : public Delegate
	{
		TFunction function;
	public:
		StaticDelegate(TFunction function)
			: Delegate(DelegateType::Static),
			function{ function }{}
		virtual void Process(TArgs... args) override {
			function(args...);
		}
		bool Compare(TFunction function) const {
			return this->function == function;
		}
	};

	template <typename TClass, typename TMethod>
	class ObjectiveDelegate : public Delegate {
		TClass* object;
		TMethod method;
	public:
		ObjectiveDelegate(TClass* object, TMethod method)
			: Delegate(DelegateType::Objective), object{ object }, method{ method }{}
		virtual void Process(TArgs...args) override {
			(object->*method)(args...);
		}
		bool Compare(TClass* object, TMethod method) const {
			return this->object == object && this->method == method;
		}
	};

	std::list<std::shared_ptr<Delegate>> delegates;

public:
	template <typename TFunction>
	void Add(TFunction function) {
		delegates.push_back(std::make_shared<StaticDelegate<TFunction>>(function));
	}
	template <typename TClass, typename TMethod>
	void Add(TClass* object, TMethod method) {
		delegates.push_back(std::make_shared<ObjectiveDelegate<TClass, TMethod>>(object, method));
	}
	template <typename TFunction>
	void Remove(TFunction function) {
		for (auto& d : delegates){
			if (d->GetType() == DelegateType::Static) {
				auto sd = std::dynamic_pointer_cast<StaticDelegate<TFunction>>(d);
				if (sd) {
					if (sd->Compare(function)) {
						delegates.remove(d);
						return;
					}
				}
			}
		}
	}
	template <typename TClass, typename TMethod>
	void Remove(TClass* object, TMethod method) {
		for (auto& d : delegates) {
			if (d->GetType() == DelegateType::Static) {
				auto sd = std::dynamic_pointer_cast<ObjectiveDelegate<TClass, TMethod>>(d);
				if (sd) {
					if (sd->Compare(object, method)) {
						delegates.remove(d);
						return;
					}
				}
			}
		}
	}

	void Process(TArgs ... args) {
		for (auto& d : delegates) {
			d->Process(args...);
		}
	}

	void operator()(TArgs... args) {
		Process(args...);
	}
};