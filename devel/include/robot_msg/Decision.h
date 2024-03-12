// Generated by gencpp from file robot_msg/Decision.msg
// DO NOT EDIT!


#ifndef ROBOT_MSG_MESSAGE_DECISION_H
#define ROBOT_MSG_MESSAGE_DECISION_H


#include <string>
#include <vector>
#include <memory>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>

#include <std_msgs/Header.h>

namespace robot_msg
{
template <class ContainerAllocator>
struct Decision_
{
  typedef Decision_<ContainerAllocator> Type;

  Decision_()
    : header()
    , yaw(0.0)
    , pitch(0.0)
    , target_lock(0)
    , fire_command(0)
    , fire_mode(0)
    , score(0)  {
    }
  Decision_(const ContainerAllocator& _alloc)
    : header(_alloc)
    , yaw(0.0)
    , pitch(0.0)
    , target_lock(0)
    , fire_command(0)
    , fire_mode(0)
    , score(0)  {
  (void)_alloc;
    }



   typedef  ::std_msgs::Header_<ContainerAllocator>  _header_type;
  _header_type header;

   typedef float _yaw_type;
  _yaw_type yaw;

   typedef float _pitch_type;
  _pitch_type pitch;

   typedef int8_t _target_lock_type;
  _target_lock_type target_lock;

   typedef int8_t _fire_command_type;
  _fire_command_type fire_command;

   typedef int8_t _fire_mode_type;
  _fire_mode_type fire_mode;

   typedef int8_t _score_type;
  _score_type score;





  typedef boost::shared_ptr< ::robot_msg::Decision_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::robot_msg::Decision_<ContainerAllocator> const> ConstPtr;

}; // struct Decision_

typedef ::robot_msg::Decision_<std::allocator<void> > Decision;

typedef boost::shared_ptr< ::robot_msg::Decision > DecisionPtr;
typedef boost::shared_ptr< ::robot_msg::Decision const> DecisionConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::robot_msg::Decision_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::robot_msg::Decision_<ContainerAllocator> >::stream(s, "", v);
return s;
}


template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator==(const ::robot_msg::Decision_<ContainerAllocator1> & lhs, const ::robot_msg::Decision_<ContainerAllocator2> & rhs)
{
  return lhs.header == rhs.header &&
    lhs.yaw == rhs.yaw &&
    lhs.pitch == rhs.pitch &&
    lhs.target_lock == rhs.target_lock &&
    lhs.fire_command == rhs.fire_command &&
    lhs.fire_mode == rhs.fire_mode &&
    lhs.score == rhs.score;
}

template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator!=(const ::robot_msg::Decision_<ContainerAllocator1> & lhs, const ::robot_msg::Decision_<ContainerAllocator2> & rhs)
{
  return !(lhs == rhs);
}


} // namespace robot_msg

namespace ros
{
namespace message_traits
{





template <class ContainerAllocator>
struct IsMessage< ::robot_msg::Decision_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::robot_msg::Decision_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::robot_msg::Decision_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::robot_msg::Decision_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::robot_msg::Decision_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::robot_msg::Decision_<ContainerAllocator> const>
  : TrueType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::robot_msg::Decision_<ContainerAllocator> >
{
  static const char* value()
  {
    return "76db552330cdcb44ee352383281c2d0d";
  }

  static const char* value(const ::robot_msg::Decision_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x76db552330cdcb44ULL;
  static const uint64_t static_value2 = 0xee352383281c2d0dULL;
};

template<class ContainerAllocator>
struct DataType< ::robot_msg::Decision_<ContainerAllocator> >
{
  static const char* value()
  {
    return "robot_msg/Decision";
  }

  static const char* value(const ::robot_msg::Decision_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::robot_msg::Decision_<ContainerAllocator> >
{
  static const char* value()
  {
    return "Header header\n"
"float32 yaw\n"
"float32 pitch\n"
"int8 target_lock\n"
"int8 fire_command\n"
"int8 fire_mode\n"
"int8 score\n"
"================================================================================\n"
"MSG: std_msgs/Header\n"
"# Standard metadata for higher-level stamped data types.\n"
"# This is generally used to communicate timestamped data \n"
"# in a particular coordinate frame.\n"
"# \n"
"# sequence ID: consecutively increasing ID \n"
"uint32 seq\n"
"#Two-integer timestamp that is expressed as:\n"
"# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')\n"
"# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')\n"
"# time-handling sugar is provided by the client library\n"
"time stamp\n"
"#Frame this data is associated with\n"
"string frame_id\n"
;
  }

  static const char* value(const ::robot_msg::Decision_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::robot_msg::Decision_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.header);
      stream.next(m.yaw);
      stream.next(m.pitch);
      stream.next(m.target_lock);
      stream.next(m.fire_command);
      stream.next(m.fire_mode);
      stream.next(m.score);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct Decision_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::robot_msg::Decision_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::robot_msg::Decision_<ContainerAllocator>& v)
  {
    s << indent << "header: ";
    s << std::endl;
    Printer< ::std_msgs::Header_<ContainerAllocator> >::stream(s, indent + "  ", v.header);
    s << indent << "yaw: ";
    Printer<float>::stream(s, indent + "  ", v.yaw);
    s << indent << "pitch: ";
    Printer<float>::stream(s, indent + "  ", v.pitch);
    s << indent << "target_lock: ";
    Printer<int8_t>::stream(s, indent + "  ", v.target_lock);
    s << indent << "fire_command: ";
    Printer<int8_t>::stream(s, indent + "  ", v.fire_command);
    s << indent << "fire_mode: ";
    Printer<int8_t>::stream(s, indent + "  ", v.fire_mode);
    s << indent << "score: ";
    Printer<int8_t>::stream(s, indent + "  ", v.score);
  }
};

} // namespace message_operations
} // namespace ros

#endif // ROBOT_MSG_MESSAGE_DECISION_H