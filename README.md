nodelet test
============

### Run
```
	(source ~/code/test_ros/devel/setup.bash)
	roslaunch nodelet_test_pkg nodelet_plus.launch
```

### test
```
rosrun nodelet nodelet manager __name:=nodelet_manager
rosrun nodelet nodelet load nodelet_ns/Plus nodelet_manager __name:=nodelet1 nodelet1/in:=foo _value:=1.1

rosrun nodelet nodelet load nodelet_ns/Plus nodelet_manager __name:=nodelet2 nodelet2/in:=foo 

rostopic pub /foo std_msgs/Float64 1.0 -r 10 
rostopic pub /test1/in std_msgs/Float64 1.0 -r 10

rostopic echo /nodelet1/out
rostopic echo /nodelet2/out
```

### node --> nodelet
```
1.Work in progress...(see nodelet_tutorial_math for an example)

add the necessary #includes
get rid of int main()
subclass nodelet::Nodelet
move code from constructor to onInit()
add the PLUGINLIB_EXPORT_CLASS macro
add <build_depend> and <run_depend> dependencies on nodelet in the package manifest.

add the <nodelet> item in the <export> part of the package manifest

create the .xml file to define the nodelet as a plugin
make the necessary changes to CMakeLists.txt (comment out a rosbuild_add_executable, add a rosbuild_add_library)


2.Minimal nodelet：
(1)MyNodeletClass.h

#include <nodelet/nodelet.h>
namespace example_pkg
{
    class MyNodeletClass : public nodelet::Nodelet
    {
        public:
            virtual void onInit();
    };
}

(2)MyNodeletClass.cpp
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

(3)nodelet_plugins.xml
  <library path="lib/libMyNodeletClass">
  <class name="example_pkg/MyNodeletClass" type="example_pkg::MyNodeletClass" base_class_type="nodelet::Nodelet">

  <description>
  This is my nodelet.
  </description>
  </class>
</library>

(4)package.xml
...
<build_depend>nodelet</build_depend>
<run_depend>nodelet</run_depend>
<export>
  <nodelet plugin="${prefix}/nodelet_plugins.xml" />
</export>
...

(5)mynodelet.launch
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