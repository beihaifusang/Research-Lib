// Generated by gencpp from file perception_msgs/radar_targets.msg
// DO NOT EDIT!


#ifndef PERCEPTION_MSGS_MESSAGE_RADAR_TARGETS_H
#define PERCEPTION_MSGS_MESSAGE_RADAR_TARGETS_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>

#include <std_msgs/Header.h>
#include <perception_msgs/radar_target.h>

namespace perception_msgs
{
template <class ContainerAllocator>
struct radar_targets_
{
  typedef radar_targets_<ContainerAllocator> Type;

  radar_targets_()
    : header()
    , timestamp_start(0)
    , timestamp_end(0)
    , target_count(0)
    , radar_targets()  {
    }
  radar_targets_(const ContainerAllocator& _alloc)
    : header(_alloc)
    , timestamp_start(0)
    , timestamp_end(0)
    , target_count(0)
    , radar_targets(_alloc)  {
  (void)_alloc;
    }



   typedef  ::std_msgs::Header_<ContainerAllocator>  _header_type;
  _header_type header;

   typedef uint64_t _timestamp_start_type;
  _timestamp_start_type timestamp_start;

   typedef uint64_t _timestamp_end_type;
  _timestamp_end_type timestamp_end;

   typedef uint32_t _target_count_type;
  _target_count_type target_count;

   typedef std::vector< ::perception_msgs::radar_target_<ContainerAllocator> , typename ContainerAllocator::template rebind< ::perception_msgs::radar_target_<ContainerAllocator> >::other >  _radar_targets_type;
  _radar_targets_type radar_targets;





  typedef boost::shared_ptr< ::perception_msgs::radar_targets_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::perception_msgs::radar_targets_<ContainerAllocator> const> ConstPtr;

}; // struct radar_targets_

typedef ::perception_msgs::radar_targets_<std::allocator<void> > radar_targets;

typedef boost::shared_ptr< ::perception_msgs::radar_targets > radar_targetsPtr;
typedef boost::shared_ptr< ::perception_msgs::radar_targets const> radar_targetsConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::perception_msgs::radar_targets_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::perception_msgs::radar_targets_<ContainerAllocator> >::stream(s, "", v);
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
struct IsFixedSize< ::perception_msgs::radar_targets_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::perception_msgs::radar_targets_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::perception_msgs::radar_targets_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::perception_msgs::radar_targets_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::perception_msgs::radar_targets_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::perception_msgs::radar_targets_<ContainerAllocator> const>
  : TrueType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::perception_msgs::radar_targets_<ContainerAllocator> >
{
  static const char* value()
  {
    return "0e87e65c3dc7e735be3e557ef8274d2e";
  }

  static const char* value(const ::perception_msgs::radar_targets_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x0e87e65c3dc7e735ULL;
  static const uint64_t static_value2 = 0xbe3e557ef8274d2eULL;
};

template<class ContainerAllocator>
struct DataType< ::perception_msgs::radar_targets_<ContainerAllocator> >
{
  static const char* value()
  {
    return "perception_msgs/radar_targets";
  }

  static const char* value(const ::perception_msgs::radar_targets_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::perception_msgs::radar_targets_<ContainerAllocator> >
{
  static const char* value()
  {
    return "Header header\n\
uint64 timestamp_start\n\
uint64 timestamp_end\n\
uint32 target_count\n\
radar_target[] radar_targets\n\
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
MSG: perception_msgs/radar_target\n\
Header header\n\
uint64 timestamp  # unit: us\n\
uint32 group_id  # radar id (front: 0  left front: 1  right front:2\n\
 # back: 3  left back: 4  right back: 5)\n\
uint32 radar_type # detail radar version\n\
 # DELPHI_ESR = 0, DELPHI_RSDS = 1,\n\
 # CONTI_408 = 2, CONTI_208 = 3,\n\
 # append if more types will be supported\n\
 # unknown = other values\n\
uint32 target_id  # target id given by radar itself\n\
uint32 track_status  # target status (need to merge with conti408 obj_MeasState)\n\
 # 0x0:No_Target\n\
 # 0x1:New_Target\n\
 # 0x2:New_Updated_Target\n\
 # 0x3:Updated_Target\n\
 # 0x4:Coasted_Target\n\
 # 0x5:Merged_Target\n\
 # 0x6:Invalid_Coasted_Target\n\
 # 0x7:New_Coasted_Target\n\
uint32 moving_status  # 0x0: moving\n\
 # 0x1: stationary\n\
 # 0x2: oncoming\n\
 # 0x3: stationary candidate\n\
 # 0x4: unknown\n\
 # 0x5: crossing stationary\n\
 # 0x6: crossing moving\n\
 # 0x7: stopped\n\
uint32 obj_type  # 0x0: point\n\
 # 0x1: car\n\
 # 0x2: truck\n\
 # 0x3: pedestrian\n\
 # 0x4: motorcycle\n\
 # 0x5: bicycle\n\
 # 0x6: wide\n\
 # 0x7: reserved\n\
 # 0x8: bridge\n\
 # 0x9: curb\n\
coord3d coordinate  # relative position (unit: m  up, front, left is positive)\n\
coord3d velocity  # relative velocity(unit: m/s  awaying is positive)\n\
bool is_radial_velocity  # set true if it's radial velocity\n\
coord3d acceleration  # relative acceleration (unit: m/s^2  awaying is positive)\n\
coord3d coordinate_rms  # standard deviation of position(unit: m)\n\
coord3d velocity_rms  # standard deviation of velocity(unit: m/s)\n\
coord3d acceleration_rms  # standard deviation of acceleration(unit: m/s^2)\n\
coord3d size_of_box  # length, width, height (unit: m) default: -1\n\
float64 rcs  # Radar Cross Section(unit: dBm^2)\n\
float64 orientation_angle  # Orientation angle(unit: rad)\n\
float64 orientation_angle_rms  # standard deviation of orientation angle(unit: rad)\n\
float64 prob_of_exist  # probability of existence(use upper limit)  default: -1\n\
float64 prob_of_objtype  #probability of object type.\n\
float64 lifetime  # the current lifetime of track(unit: s)  default: -1\n\
bool is_acceleration_valid # set true if acceleration is valid\n\
bool is_coordinate_rms_valid # set true if valid\n\
bool is_velocity_rms_valid # set true if valid\n\
bool is_acceleration_rms_valid # set true if valid\n\
bool is_orientation_angle_valid # set true if valid\n\
bool is_orientation_angle_rms_valid # set true if valid\n\
\n\
================================================================================\n\
MSG: perception_msgs/coord3d\n\
float64 x\n\
float64 y\n\
float64 z\n\
";
  }

  static const char* value(const ::perception_msgs::radar_targets_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::perception_msgs::radar_targets_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.header);
      stream.next(m.timestamp_start);
      stream.next(m.timestamp_end);
      stream.next(m.target_count);
      stream.next(m.radar_targets);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct radar_targets_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::perception_msgs::radar_targets_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::perception_msgs::radar_targets_<ContainerAllocator>& v)
  {
    s << indent << "header: ";
    s << std::endl;
    Printer< ::std_msgs::Header_<ContainerAllocator> >::stream(s, indent + "  ", v.header);
    s << indent << "timestamp_start: ";
    Printer<uint64_t>::stream(s, indent + "  ", v.timestamp_start);
    s << indent << "timestamp_end: ";
    Printer<uint64_t>::stream(s, indent + "  ", v.timestamp_end);
    s << indent << "target_count: ";
    Printer<uint32_t>::stream(s, indent + "  ", v.target_count);
    s << indent << "radar_targets[]" << std::endl;
    for (size_t i = 0; i < v.radar_targets.size(); ++i)
    {
      s << indent << "  radar_targets[" << i << "]: ";
      s << std::endl;
      s << indent;
      Printer< ::perception_msgs::radar_target_<ContainerAllocator> >::stream(s, indent + "    ", v.radar_targets[i]);
    }
  }
};

} // namespace message_operations
} // namespace ros

#endif // PERCEPTION_MSGS_MESSAGE_RADAR_TARGETS_H