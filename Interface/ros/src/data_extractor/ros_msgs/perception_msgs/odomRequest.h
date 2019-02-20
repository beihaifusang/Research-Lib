// Generated by gencpp from file perception_msgs/odomRequest.msg
// DO NOT EDIT!


#ifndef PERCEPTION_MSGS_MESSAGE_ODOMREQUEST_H
#define PERCEPTION_MSGS_MESSAGE_ODOMREQUEST_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace perception_msgs
{
template <class ContainerAllocator>
struct odomRequest_
{
  typedef odomRequest_<ContainerAllocator> Type;

  odomRequest_()
    : mode(0)
    , time_ms(0)
    , time_us(0)
    , time_ns(0)  {
    }
  odomRequest_(const ContainerAllocator& _alloc)
    : mode(0)
    , time_ms(0)
    , time_us(0)
    , time_ns(0)  {
  (void)_alloc;
    }



   typedef int64_t _mode_type;
  _mode_type mode;

   typedef uint64_t _time_ms_type;
  _time_ms_type time_ms;

   typedef uint64_t _time_us_type;
  _time_us_type time_us;

   typedef uint64_t _time_ns_type;
  _time_ns_type time_ns;





  typedef boost::shared_ptr< ::perception_msgs::odomRequest_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::perception_msgs::odomRequest_<ContainerAllocator> const> ConstPtr;

}; // struct odomRequest_

typedef ::perception_msgs::odomRequest_<std::allocator<void> > odomRequest;

typedef boost::shared_ptr< ::perception_msgs::odomRequest > odomRequestPtr;
typedef boost::shared_ptr< ::perception_msgs::odomRequest const> odomRequestConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::perception_msgs::odomRequest_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::perception_msgs::odomRequest_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace perception_msgs

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': True, 'IsMessage': True, 'HasHeader': False}
// {'perception_msgs': ['/home/shawn/baidu/ai-auto/l3-apollo/catkin_build/src/modules/ros_msgs/perception/msg'], 'std_msgs': ['/opt/ros/kinetic/share/std_msgs/cmake/../msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::perception_msgs::odomRequest_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::perception_msgs::odomRequest_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::perception_msgs::odomRequest_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::perception_msgs::odomRequest_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::perception_msgs::odomRequest_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::perception_msgs::odomRequest_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::perception_msgs::odomRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "01def5bbf5f8a4ab4a980659b555e400";
  }

  static const char* value(const ::perception_msgs::odomRequest_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x01def5bbf5f8a4abULL;
  static const uint64_t static_value2 = 0x4a980659b555e400ULL;
};

template<class ContainerAllocator>
struct DataType< ::perception_msgs::odomRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "perception_msgs/odomRequest";
  }

  static const char* value(const ::perception_msgs::odomRequest_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::perception_msgs::odomRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "int64 mode\n\
uint64 time_ms\n\
uint64 time_us\n\
uint64 time_ns\n\
";
  }

  static const char* value(const ::perception_msgs::odomRequest_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::perception_msgs::odomRequest_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.mode);
      stream.next(m.time_ms);
      stream.next(m.time_us);
      stream.next(m.time_ns);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct odomRequest_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::perception_msgs::odomRequest_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::perception_msgs::odomRequest_<ContainerAllocator>& v)
  {
    s << indent << "mode: ";
    Printer<int64_t>::stream(s, indent + "  ", v.mode);
    s << indent << "time_ms: ";
    Printer<uint64_t>::stream(s, indent + "  ", v.time_ms);
    s << indent << "time_us: ";
    Printer<uint64_t>::stream(s, indent + "  ", v.time_us);
    s << indent << "time_ns: ";
    Printer<uint64_t>::stream(s, indent + "  ", v.time_ns);
  }
};

} // namespace message_operations
} // namespace ros

#endif // PERCEPTION_MSGS_MESSAGE_ODOMREQUEST_H
