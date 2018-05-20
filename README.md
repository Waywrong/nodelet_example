nodelet test
============

### Run
```
	(source ~/code/test_ros/devel/setup.bash)
	roslaunch nodelet_test_pkg nodelet_test.launch
```
### node --> nodelet
```

1.流程：

（1）添加必要的 #includes。

（2）移除主函数int main()。

（3）创建nodelet::Nodelet子类。

（4）把构造函数移植到onInit()。

（5）添加PLUGINLIB_EXPORT_CLASS宏定义。

（6）在package.xml中添加nodelet编译、运行依赖项nodelet。

（7）将nodelet加入到package.xml的<export> 部分。

（8）定义.xml文件使nodelet成为一个插件。

（9）在CMakeLists.txt中添加rosbuild_add_executable, add a rosbuild_add_library。

2.最小的nodelet：

（1）MyNodeletClass.h


#include <nodelet/nodelet.h>
namespace example_pkg
{
    class MyNodeletClass : public nodelet::Nodelet
    {
        public:
            virtual void onInit();
    };
}

（2）MyNodeletClass.cpp

// this should really be in the implementation (.cpp file)
#include <pluginlib/class_list_macros.h>
// watch the capitalization carefully
PLUGINLIB_EXPORT_CLASS(example_pkg::MyNodeletClass, nodelet::Nodelet) 
namespace example_pkg
{
    void MyNodeletClass::onInit() 
    {
        NODELET_DEBUG("Initializing nodelet...");
    }
}

（3）nodelet_plugins.xml
  <library path="lib/libMyNodeletClass">
  <class name="example_pkg/MyNodeletClass" type="example_pkg::MyNodeletClass" base_class_type="nodelet::Nodelet">

  <description>
  This is my nodelet.
  </description>
  </class>
</library>

（4）package.xml
...
<build_depend>nodelet</build_depend>
<run_depend>nodelet</run_depend>
<export>
  <nodelet plugin="${prefix}/nodelet_plugins.xml" />
</export>
...

（5）mynodelet.launch
<launch>
  <node pkg="nodelet" type="nodelet" name="standalone_nodelet"  args="manager" output="screen"/>
  <node pkg="nodelet" type="nodelet" name="MyNodeletClass" args="load example_pkg/MyNodeletClass standalone_nodelet" output="screen">
  </node>                 
</launch>
```

### Reference
```
	https://blog.csdn.net/zyh821351004/article/details/52143309
	https://my.oschina.net/sunzhiming/blog/408168
```