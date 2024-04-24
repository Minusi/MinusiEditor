#pragma once


namespace Editor
{
	template<class Derived>
	class Singleton
	{
	protected:
		Singleton(const Singleton&) = delete;
		Singleton(const Singleton&&) = delete;
		Singleton& operator=(const Singleton&) = delete;
		Singleton& operator=(const Singleton&&) = delete;

		Singleton() = default;
		virtual ~Singleton() = default;

	protected:
		virtual void Initialize() {}
		virtual void Finalize() {}

	public:
		static Derived* Instance() { return _Instance; }
		static Derived* CreateInstance()
		{
			if (_Instance == nullptr)
			{
				_Instance = new Derived();
				return _Instance;
			}

			assert(_Instance == nullptr);
			return _Instance;
		}
		static void DestroyInstance()
		{
			if (_Instance == nullptr)
			{
				assert(_Instance);
				return;
			}

			delete _Instance;
			_Instance = nullptr;
		}
		
	private:
		static Derived* _Instance;
	};

	template<typename Derived> Derived* Singleton<Derived>::_Instance = nullptr;

#define DECLARE_SINGLETON(ClassName)		\
	private:								\
		ClassName() { Initialize(); }		\
		~ClassName() { Finalize(); }		\
		friend class Singleton<ClassName>;
}