#ifndef __FILE_H__
#define __FILE_H__

#define private public
#define protected public

#include <base/FDWrapper.h>
#include <memory>

#include <base/pgfwd.h>

namespace pg::base {

// bool readable()	测试应用程序是否能从指定的文件中进行读取
// bool writable()	测试应用程序是否能写当前文件
// bool remove()	删除当前对象指定的文件
// bool exists()	测试当前 File 是否存在
// std::string getAbsolutePath()	返回由该对象表示的文件的绝对路径名
// std::string getName()	返回表示当前对象的文件名或路径名（如果是路径，则返回最后一级子路径名）
// std::string getParent()	返回当前 File 对象所对应目录（最后一级子目录）的父目录名
// bool isAbsolute()	测试当前 File 对象表示的文件是否为一个绝对路径名。该方法消除了不同平台的差异，可以直接判断 file 对象是否为绝对路径。在 UNIX/Linux/BSD 等系统上，如果路径名开头是一条斜线/，则表明该 File 对象对应一个绝对路径；在 Windows 等系统上，如果路径开头是盘符，则说明它是一个绝对路径。
// bool isDir()	测试当前 File 对象表示的文件是否为一个路径
// bool isFile()	测试当前 File 对象表示的文件是否为一个“普通”文件
// pg::timetamp_t lastModified()	返回当前 File 对象表示的文件最后修改的时间
// std::size_t size()	返回当前 File 对象表示的文件长度
// pg::type::Group<std::string> list()	返回当前 File 对象指定的路径的文件列表
// pg::type::Group<std::string> list(_Con & condition)	返回当前 File 对象指定的目录中满足指定过滤器的文件列表
// bool mkdir()	创建一个目录，它的路径名由当前 File 对象指定
// bool mkdirs()	创建一个目录，它的路径名由当前 File 对象指定
// bool rename(const std::string &)	文件更名为给定name, no-path
// bool move(const std::string & path)
// bool move(const pg::base::File & target) move the File to target-path, 
//                                          if the target is a file, mv to its parent-path



} // namespace pg::base

#endif