// Generated by gencpp from file perception_msgs/vehicle_angular_rates.msg
// DO NOT EDIT!


#ifndef PERCEPTION_MSGS_MESSAGE_VEHICLE_ANGULAR_RATES_H
#define PERCEPTION_MSGS_MESSAGE_VEHICLE_ANGULAR_RATES_H


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
struct vehicle_angular_rates_
{
  typedef vehicle_angular_rates_<ContainerAllocator> Type;

  vehicle_angular_rates_()
    : header()
    , roll_isvalid(false)
    , yaw_isvalid(false)
    , pitch_isvalid(false)
    , roll(0.0)
    , yaw(0.0)
    , pitch(0.0)  {
    }
  vehicle_angular_rates_(const ContainerAllocator& _alloc)
    : header(_alloc)
    , roll_isvalid(false)
    , yaw_isvalid(false)
    , pitch_isvalid(false)
    , roll(0.0)
    , yaw(0.0)
    , pitch(0.0)  {
  (void)_alloc;
    }



   typedef  ::std_msgs::Header_<ContainerAllocator>  _header_type;
  _header_type header;

   typedef uint8_t _roll_isvalid_type;
  _roll_isvalid_type roll_isvalid;

   typedef uint8_t _yaw_isvalid_type;
  _yaw_isvalid_type yaw_isvalid;

   typedef uint8_t _pitch_isvalid_type;
  _pitch_isvalid_type pitch_isvalid;

   typedef double _roll_type;
  _roll_type roll;

   typedef double _yaw_type;
  _yaw_type yaw;

   typedef double _pitch_type;
  _pitch_type pitch;





  typedef boost::shared_ptr< ::perception_msgs::vehicle_angular_rates_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::perception_msgs::vehicle_angular_rates_<ContainerAllocator> const> ConstPtr;

}; // struct vehicle_angular_rates_

typedef ::perception_msgs::vehicle_angular_rates_<std::allocator<void> > vehicle_angular_rates;

typedef boost::shared_ptr< ::perception_msgs::vehicle_angular_rates > vehicle_angular_ratesPtr;
typedef boost::shared_ptr< ::perception_msgs::vehicle_angular_rates const> vehicle_angular_ratesConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::perception_msgs::vehicle_angular_rates_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::perception_msgs::vehicle_angular_rates_<ContainerAllocator> >::stream(s, "", v);
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
struct IsFixedSize< ::perception_msgs::vehicle_angular_rates_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::perception_msgs::vehicle_angular_rates_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::perception_msgs::vehicle_angular_rates_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::perception_msgs::vehicle_angular_rates_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::perception_msgs::vehicle_angular_rates_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::perception_msgs::vehicle_angular_rates_<ContainerAllocator> const>
  : TrueType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::perception_msgs::vehicle_angular_rates_<ContainerAllocator> >
{
  static const char* value()
  {
    return "fb04d745705770f46fd6862b0f002ff1";
  }

  static const char* value(const ::perception_msgs::vehicle_angular_rates_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xfb04d745705770f4ULL;
  static const uint64_t static_value2 = 0x6fd6862b0f002ff1ULL;
};

template<class ContainerAllocator>
struct DataType< ::perception_msgs::vehicle_angular_rates_<ContainerAllocator> >
{
  static const char* value()
  {
    return "perception_msgs/vehicle_angular_rates";
  }

  static const char* value(const ::perception_msgs::vehicle_angular_rates_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::perception_msgs::vehicle_angular_rates_<ContainerAllocator> >
{
  static const char* value()
  {
    return "Header header\n\
bool roll_isvalid\n\
bool yaw_isvalid\n\
bool pitch_isvalid\n\
\n\
float64 roll 		#翻转角 单位rad/s 取值[-6.5536,6.5534] \n\
float64 yaw		#偏行角 单位rad/s 取值[-6.5536,6.5534] \n\
float64 pitch		#俯养角 单位rad/s 取值[-6.5536,6.5534] \n\
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

  static const char* value(const ::perception_msgs::vehicle_angular_rates_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::perception_msgs::vehicle_angular_rates_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.header);
      stream.next(m.roll_isvalid);
      stream.next(m.yaw_isvalid);
      stream.next(m.pitch_isvalid);
      stream.next(m.roll);
      stream.next(m.yaw);
      stream.next(m.pitch);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct vehicle_angular_rates_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::perception_msgs::vehicle_angular_rates_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::perception_msgs::vehicle_angular_rates_<ContainerAllocator>& v)
  {
    s << indent << "header: ";
    s << std::endl;
    Printer< ::std_msgs::Header_<ContainerAllocator> >::stream(s, indent + "  ", v.header);
    s << indent << "roll_isvalid: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.roll_isvalid);
    s << indent << "yaw_isvalid: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.yaw_isvalid);
    s << indent << "pitch_isvalid: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.pitch_isvalid);
    s << indent << "roll: ";
    Printer<double>::stream(s, indent + "  ", v.roll);
    s << indent << "yaw: ";
    Printer<double>::stream(s, indent + "  ", v.yaw);
    s << indent << "pitch: ";
    Printer<double>::stream(s, indent + "  ", v.pitch);
  }
};

} // namespace message_operations
} // namespace ros

#endif // PERCEPTION_MSGS_MESSAGE_VEHICLE_ANGULAR_RATES_H
