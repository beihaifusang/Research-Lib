// Generated by gencpp from file perception_msgs/vehicle_info.msg
// DO NOT EDIT!


#ifndef PERCEPTION_MSGS_MESSAGE_VEHICLE_INFO_H
#define PERCEPTION_MSGS_MESSAGE_VEHICLE_INFO_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>

#include <std_msgs/Header.h>

namespace perception_msgs
{
template <class ContainerAllocator>
struct vehicle_info_
{
  typedef vehicle_info_<ContainerAllocator> Type;

  vehicle_info_()
    : header()
    , heading_lane(0.0)
    , dist_to_line(0.0)
    , is_pressed_line(false)
    , pressed_lane_id(0)
    , current_speed(0.0)
    , longitude(0.0)
    , latitude(0.0)
    , height(0.0)
    , roll(0.0)
    , pitch(0.0)
    , yaw(0.0)  {
    }
  vehicle_info_(const ContainerAllocator& _alloc)
    : header(_alloc)
    , heading_lane(0.0)
    , dist_to_line(0.0)
    , is_pressed_line(false)
    , pressed_lane_id(0)
    , current_speed(0.0)
    , longitude(0.0)
    , latitude(0.0)
    , height(0.0)
    , roll(0.0)
    , pitch(0.0)
    , yaw(0.0)  {
  (void)_alloc;
    }



   typedef  ::std_msgs::Header_<ContainerAllocator>  _header_type;
  _header_type header;

   typedef double _heading_lane_type;
  _heading_lane_type heading_lane;

   typedef double _dist_to_line_type;
  _dist_to_line_type dist_to_line;

   typedef uint8_t _is_pressed_line_type;
  _is_pressed_line_type is_pressed_line;

   typedef int32_t _pressed_lane_id_type;
  _pressed_lane_id_type pressed_lane_id;

   typedef double _current_speed_type;
  _current_speed_type current_speed;

   typedef double _longitude_type;
  _longitude_type longitude;

   typedef double _latitude_type;
  _latitude_type latitude;

   typedef double _height_type;
  _height_type height;

   typedef double _roll_type;
  _roll_type roll;

   typedef double _pitch_type;
  _pitch_type pitch;

   typedef double _yaw_type;
  _yaw_type yaw;





  typedef boost::shared_ptr< ::perception_msgs::vehicle_info_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::perception_msgs::vehicle_info_<ContainerAllocator> const> ConstPtr;

}; // struct vehicle_info_

typedef ::perception_msgs::vehicle_info_<std::allocator<void> > vehicle_info;

typedef boost::shared_ptr< ::perception_msgs::vehicle_info > vehicle_infoPtr;
typedef boost::shared_ptr< ::perception_msgs::vehicle_info const> vehicle_infoConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::perception_msgs::vehicle_info_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::perception_msgs::vehicle_info_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace perception_msgs

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': False, 'IsMessage': True, 'HasHeader': True}
// {'perception_msgs': ['/home/shawn/baidu/ai-auto/l3-apollo/catkin_build/src/modules/ros_msgs/perception/msg'], 'std_msgs': ['/opt/ros/kinetic/share/std_msgs/cmake/../msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::perception_msgs::vehicle_info_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::perception_msgs::vehicle_info_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::perception_msgs::vehicle_info_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::perception_msgs::vehicle_info_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::perception_msgs::vehicle_info_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::perception_msgs::vehicle_info_<ContainerAllocator> const>
  : TrueType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::perception_msgs::vehicle_info_<ContainerAllocator> >
{
  static const char* value()
  {
    return "97c6f742b1d8518d14506d0562e2561c";
  }

  static const char* value(const ::perception_msgs::vehicle_info_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x97c6f742b1d8518dULL;
  static const uint64_t static_value2 = 0x14506d0562e2561cULL;
};

template<class ContainerAllocator>
struct DataType< ::perception_msgs::vehicle_info_<ContainerAllocator> >
{
  static const char* value()
  {
    return "perception_msgs/vehicle_info";
  }

  static const char* value(const ::perception_msgs::vehicle_info_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::perception_msgs::vehicle_info_<ContainerAllocator> >
{
  static const char* value()
  {
    return "Header header\n\
float64 heading_lane   #/*!< 当前车道与Host车辆坐标系x轴夹角,绕x轴旋转，弧度单位,取值范围：(0 – 2π) */\n\
float64 dist_to_line   #/*!< 到右侧车道线距离 */\n\
bool is_pressed_line   #/*!< Host车是否压到车道线上 */\n\
int32 pressed_lane_id  #/*!< Host车压到的车道ID */\n\
float64 current_speed  #/*!< 当前车速 */\n\
float64 longitude      #/*!< 高精地图坐标 x 经度 */\n\
float64 latitude       #/*!< 高精地图坐标 y 纬度 */\n\
float64 height         #/*!< 高精地图坐标 z 高程 */\n\
\n\
#/*!< 北东天坐标系 高精地图坐标到车身坐标的变换角*/\n\
float64 roll           #/*!< 参考INS/IMU输出,弧度单位,取值范围：(0 – 2π) */\n\
float64 pitch          #/*!< 参考INS/IMU输出,弧度单位, 取值范围：(0 – 2π)*/\n\
float64 yaw            #/*!< 参考INS/IMU输出,弧度单位,取值范围：(0 – 2π) */\n\
\n\
\n\
================================================================================\n\
MSG: std_msgs/Header\n\
# Standard metadata for higher-level stamped data types.\n\
# This is generally used to communicate timestamped data \n\
# in a particular coordinate frame.\n\
# \n\
# sequence ID: consecutively increasing ID \n\
uint32 seq\n\
#Two-integer timestamp that is expressed as:\n\
# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')\n\
# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')\n\
# time-handling sugar is provided by the client library\n\
time stamp\n\
#Frame this data is associated with\n\
# 0: no frame\n\
# 1: global frame\n\
string frame_id\n\
";
  }

  static const char* value(const ::perception_msgs::vehicle_info_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::perception_msgs::vehicle_info_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.header);
      stream.next(m.heading_lane);
      stream.next(m.dist_to_line);
      stream.next(m.is_pressed_line);
      stream.next(m.pressed_lane_id);
      stream.next(m.current_speed);
      stream.next(m.longitude);
      stream.next(m.latitude);
      stream.next(m.height);
      stream.next(m.roll);
      stream.next(m.pitch);
      stream.next(m.yaw);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct vehicle_info_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::perception_msgs::vehicle_info_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::perception_msgs::vehicle_info_<ContainerAllocator>& v)
  {
    s << indent << "header: ";
    s << std::endl;
    Printer< ::std_msgs::Header_<ContainerAllocator> >::stream(s, indent + "  ", v.header);
    s << indent << "heading_lane: ";
    Printer<double>::stream(s, indent + "  ", v.heading_lane);
    s << indent << "dist_to_line: ";
    Printer<double>::stream(s, indent + "  ", v.dist_to_line);
    s << indent << "is_pressed_line: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.is_pressed_line);
    s << indent << "pressed_lane_id: ";
    Printer<int32_t>::stream(s, indent + "  ", v.pressed_lane_id);
    s << indent << "current_speed: ";
    Printer<double>::stream(s, indent + "  ", v.current_speed);
    s << indent << "longitude: ";
    Printer<double>::stream(s, indent + "  ", v.longitude);
    s << indent << "latitude: ";
    Printer<double>::stream(s, indent + "  ", v.latitude);
    s << indent << "height: ";
    Printer<double>::stream(s, indent + "  ", v.height);
    s << indent << "roll: ";
    Printer<double>::stream(s, indent + "  ", v.roll);
    s << indent << "pitch: ";
    Printer<double>::stream(s, indent + "  ", v.pitch);
    s << indent << "yaw: ";
    Printer<double>::stream(s, indent + "  ", v.yaw);
  }
};

} // namespace message_operations
} // namespace ros

#endif // PERCEPTION_MSGS_MESSAGE_VEHICLE_INFO_H
