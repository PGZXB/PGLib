#include <base/File.h>

#include <errno.h>

#include <cctype>

#ifdef linux
const char pg::base::File::PATH_SEPARATOR = '/';
// #elif defined _WIN32
// const char pg::base::File::PATH_SEPARATOR = '\\';
#endif

pg::base::File::File(const std::string & pathname) : path_(pathname) { // 通过将给定路径名字符串转换成抽象路径名来创建一个新 File 实例。
    initCheck();
}

pg::base::File::File(const File & parent, const std::string & child) : path_(parent.path_ + child) { // 通过给定的父抽象路径名和子路径名字符串创建一个新的File实例。
    initCheck();
}

pg::base::File::File(const std::string & parent, const std::string & child) : path_(parent + child) { // 根据 parent 路径名字符串和 child 路径名字符串创建一个新 File 实例。
    initCheck();
} 

// public-member-functions
bool pg::base::File::readable() const { // 测试应用程序是否能从指定的文件中进行读取
    __uid_t uid = getuid();
    __gid_t gid = getgid();

    if (gid == stat_.st_gid) {
        if (uid == stat_.st_uid)
            return stat_.st_mode & S_IRUSR;
        return stat_.st_mode & S_IRGRP;
    }
    
    return stat_.st_mode & S_IROTH;
}

bool pg::base::File::writable() const { // 测试应用程序是否能写当前文件
    __uid_t uid = getuid();
    __gid_t gid = getgid();
    
    if (gid == stat_.st_gid) {
        if (uid == stat_.st_uid)
            return stat_.st_mode & S_IWUSR;
        return stat_.st_mode & S_IWGRP;
    }
    
    return stat_.st_mode & S_IWOTH;
}

bool pg::base::File::remove() { // 删除当前对象指定的文件
    return false;
}

bool pg::base::File::exists() const { // 测试当前 File 是否存在
    return exists_;
}

std::string pg::base::File::getAbsolutePath() const { // 返回由该对象表示的文件的绝对路径名
    return isAbsolute() ? path_ : std::string(get_current_dir_name()).append(1, PATH_SEPARATOR).append(path_);
}

std::string pg::base::File::getName() const { // 返回表示当前对象的文件名或路径名（如果是路径，则返回最后一级子路径名）
    std::string::size_type pos = path_.find_last_of(File::PATH_SEPARATOR);
    if (pos == std::string::npos) return path_;

    return std::string(path_.begin() + pos + 1, path_.end());
}

std::string pg::base::File::getParent() const { // 返回当前 File 对象所对应目录（最后一级子目录）的父目录名
    std::string::size_type pos = getAbsolutePath().find_last_of(PATH_SEPARATOR);
    if (pos == path_.size() - 1) return path_;

    return std::string(path_.begin(), path_.begin() + pos);
}

bool pg::base::File::isAbsolute() const { // 测试当前 File 对象表示的文件是否为一个绝对路径名。该方法消除了不同平台的差异，可以直接判断 file 对象是否为绝对路径。在 UNIX/Linux/BSD 等系统上，如果路径名开头是一条斜线/，则表明该 File 对象对应一个绝对路径；在 Windows 等系统上，如果路径开头是盘符，则说明它是一个绝对路径。
#ifdef linux
    return !path_.empty() && path_[0] == PATH_SEPARATOR;
// #elif defined _WIN32
//     return !path_.empty() && std::isalpha(path[0]); 
#endif
}

bool pg::base::File::isDir() const { // 测试当前 File 对象表示的文件是否为一个路径
    return S_ISDIR(stat_.st_mode);
}

bool pg::base::File::isFile() const { // 测试当前 File 对象表示的文件是否为一个“普通”文件
    return !( S_ISDIR(stat_.st_mode) );
}

long/*pg::type::timetamp_t*/ pg::base::File::lastModified() const { // 返回当前 File 对象表示的文件最后修改的时间
    return 0L;
}

std::size_t pg::base::File::size() const { // 返回当前 File 对象表示的文件长度
    return stat_.st_size;
}

pg::type::Group<std::string> pg::base::File::list() const { // 返回当前 File 对象指定的路径的文件列表
    return pg::type::Group<std::string>();
}

bool pg::base::File::mkdir() { // parent must exists , 创建一个目录，它的路径名由当前 File 对象指定
    return false;
}

bool pg::base::File::mkdirs() { // no request, 创建一个目录，它的路径名由当前 File 对象指定
    return false;
}

bool pg::base::File::rename(const std::string &) { // 文件更名为给定name, no-path
    return false;
}

bool pg::base::File::move(const std::string & path) {
    return false;
}

bool pg::base::File::move(const pg::base::File & target) { 
    // move the File to target-path, 
    // if the target is a file, mv to its parent-path

    return false;
}

// PG-Like-Desigh
std::shared_ptr<pg::base::FDWrapper> pg::base::File::getFDWrapper() { // get FDWrapper, which can write/read to/from file
    using pg::base::FileOpenMode;
    using pg::base::FDWrapper;

    return std::shared_ptr<FDWrapper>(new FDWrapper(pg::base::getFd(path_, FileOpenMode::Mode(FileOpenMode::Read | FileOpenMode::Write))));
} 

std::shared_ptr<pg::base::FILEWrapper> pg::base::File::getFILEWrapper() { // get FILEWrapper, which can write/read to/from file
    using pg::base::FileOpenMode;
    using pg::base::FILEWrapper;

    return std::shared_ptr<FILEWrapper>(new FILEWrapper(pg::base::getPFILE(path_, FileOpenMode::Mode(FileOpenMode::Read | FileOpenMode::Append))));
} 

// private-functions
void pg::base::File::initCheck() {
    
    // to check if path is valid
    // ... using regex-match

    if ( path_.size() > 1 && path_.back() == PATH_SEPARATOR ) path_.pop_back();
    if (::stat(path_.c_str(), &stat_) == -1)
        if (errno == ENOENT) exists_ = false;
}