#pragma once

#include <set>

namespace Policy
{
	template<typename Key>
	class None
	{
	private:
		std::set<Key> key_storage;

	public:
		None() = default;
		~None() = default;

		void clear() { key_storage.clear(); }
		void insert(const Key& key) { key_storage.emplace(key); }
		void touch (const Key& key) { (void)key; }
		void erase (const Key& key) { key_storage.erase(key); }

		const Key& replace_candidate() const { return *key_storage.cbegin(); }
	};
}
