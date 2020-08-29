namespace std {
    template <typename T, typename Alloc>
    class vector;
} // namespace std


namespace pg {
    namespace type {

        typedef char Byte;

        template <typename T>
        using Group = std::vector<T>;
        
    } // namespace type  
} // the end of namespace pg
