#ifndef __OBJECTMANAGER_H__
#define __OBJECTMANAGER_H__

#include <unordered_map>
#include <list>
#include <utility>

namespace pg {
    
    template <typename _Class>
    class ObjectManager {
        using ObjectPointerType = _Class *;
        using ObjectRefType = _Class &;
        using ObjectType = _Class;
        using ObjectListIteratorType = typename std::list<ObjectType>::iterator;

    public:
        ~ObjectManager() = default;

        template <typename ... Args>
        ObjectPointerType createObject(Args && ... args) {
            objectPool.emplace_front(std::forward<Args>(args)...);

            ObjectPointerType ptr = &objectPool.front();

            objectIterOfPointer.insert(std::make_pair(ptr, objectPool.begin()));

            return ptr;
        }

        ObjectManager & delObject(ObjectPointerType & ptr) {

            typename std::unordered_map<ObjectPointerType, ObjectListIteratorType>::iterator iter = objectIterOfPointer.find(ptr);

            if (iter != objectIterOfPointer.end()) {
                objectPool.erase(iter->second);
                objectIterOfPointer.erase(iter);
                ptr = nullptr;
            }

            return *this;
        }

    private:
        ObjectManager() = default;
        ObjectManager(const ObjectManager &) = delete;
        ObjectManager(ObjectManager &&) = delete;

        ObjectManager & operator = (const ObjectManager &) = delete;
        ObjectManager & operator = (ObjectManager &&) = delete;

    public:
        static ObjectManager * getInstance() {
            static ObjectManager instance;

            return & instance;
        }

    private:
        std::unordered_map<ObjectPointerType, ObjectListIteratorType> objectIterOfPointer;
        std::list<ObjectType> objectPool;
    };

} // namespace pg




#endif