// Generated by gencpp from file perception_msgs/VelodyneScan.msg
// DO NOT EDIT!


#ifndef PERCEPTION_MSGS_MESSAGE_VELODYNESCAN_H
#define PERCEPTION_MSGS_MESSAGE_VELODYNESCAN_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>

#include <std_msgs/Header.h>
#include <perception_msgs/VelodynePacket.h>

namespace perception_msgs
{
template <class ContainerAllocator>
struct VelodyneScan_
{
  typedef VelodyneScan_<ContainerAllocator> Type;

  VelodyneScan_()
    : header()
    , packets()  {
    }
  VelodyneScan_(const ContainerAllocator& _alloc)
    : header(_alloc)
    , packets(_alloc)  {
  (void)_alloc;
    }



   typedef  ::std_msgs::Header_<ContainerAllocator>  _header_type;
  _header_type header;

   typedef std::vector< ::perception_msgs::VelodynePacket_<ContainerAllocator> , typename ContainerAllocator::template rebind< ::perception_msgs::VelodynePacket_<ContainerAllocator> >::other >  _packets_type;
  _packets_type packets;





  typedef boost::shared_ptr< ::perception_msgs::VelodyneScan_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::perception_msgs::VelodyneScan_<ContainerAllocator> const> ConstPtr;

}; // struct VelodyneScan_

typedef ::perception_msgs::VelodyneScan_<std::allocator<void> > VelodyneScan;

typedef boost::shared_ptr< ::perception_msgs::VelodyneScan > VelodyneScanPtr;
typedef boost::shared_ptr< ::perception_msgs::VelodyneScan const> VelodyneScanConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::perception_msgs::VelodyneScan_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::perception_msgs::VelodyneScan_<ContainerAllocator> >::stream(s, "", v);
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
struct IsFixedSize< ::perception_msgs::VelodyneScan_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::perception_msgs::VelodyneScan_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::perception_msgs::VelodyneScan_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::perception_msgs::VelodyneScan_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::perception_msgs::VelodyneScan_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::perception_msgs::VelodyneScan_<ContainerAllocator> const>
  : TrueType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::perception_msgs::VelodyneScan_<ContainerAllocator> >
{
  static const char* value()
  {
    return "50804fc9533a0e579e6322c04ae70566";
  }

  static const char* value(const ::perception_msgs::VelodyneScan_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x50804fc9533a0e57ULL;
  static const uint64_t static_value2 = 0x9e6322c04ae70566ULL;
};

template<class ContainerAllocator>
struct DataType< ::perception_msgs::VelodyneScan_<ContainerAllocator> >
{
  static const char* value()
  {
    return "perception_msgs/VelodyneScan";
  }

  static const char* value(const ::perception_msgs::VelodyneScan_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::perception_msgs::VelodyneScan_<ContainerAllocator> >
{
  static const char* value()
  {
    return "# Velodyne LIDAR scan packets.\n\
\n\
Header           header         # standard ROS message header\n\
VelodynePacket[] packets        # vector of raw packets\n\
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
\n\
================================================================================\n\
MSG: perception_msgs/VelodynePacket\n\
# Raw Velodyne LIDAR packet.\n\
\n\
time stamp              # packet timestamp\n\
uint8[1206] data        # packet contents\n\
\n\
";
  }

  static const char* value(const ::perception_msgs::VelodyneScan_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::perception_msgs::VelodyneScan_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.header);
      stream.next(m.packets);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct VelodyneScan_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::perception_msgs::VelodyneScan_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::perception_msgs::VelodyneScan_<ContainerAllocator>& v)
  {
    s << indent << "header: ";
    s << std::endl;
    Printer< ::std_msgs::Header_<ContainerAllocator> >::stream(s, indent + "  ", v.header);
    s << indent << "packets[]" << std::endl;
    for (size_t i = 0; i < v.packets.size(); ++i)
    {
      s << indent << "  packets[" << i << "]: ";
      s << std::endl;
      s << indent;
      Printer< ::perception_msgs::VelodynePacket_<ContainerAllocator> >::stream(s, indent + "    ", v.packets[i]);
    }
  }
};

} // namespace message_operations
} // namespace ros

#endif // PERCEPTION_MSGS_MESSAGE_VELODYNESCAN_H
