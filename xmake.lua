add_rules("mode.debug", "mode.release")

set_languages("c++23", "c17")--设置编译语言

set_encodings("utf-8")--设源文件编码和可执行文件输出编码 utf-8

set_project("raylib-cpp-cn")-- 设工程名

set_version("0.0.1")-- 设工程版本

add_requires("raylib 5.5") --添加依赖包

add_packages("raylib")--导入依赖包,作用全工程

add_includedirs("include",{public = true}) --添加头文件搜索路径,公开
 

includes("**/xmake.lua")--搜索目录下所有子构建

add_defines("ROOT")--添加宏定义