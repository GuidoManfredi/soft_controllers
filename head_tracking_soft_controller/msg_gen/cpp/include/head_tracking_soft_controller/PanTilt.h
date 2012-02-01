/* Auto-generated by genmsg_cpp for file /u/gmanfred/ros/release/soft_controllers/head_tracking_soft_controller/msg/PanTilt.msg */
#ifndef HEAD_TRACKING_SOFT_CONTROLLER_MESSAGE_PANTILT_H
#define HEAD_TRACKING_SOFT_CONTROLLER_MESSAGE_PANTILT_H
#include <string>
#include <vector>
#include <map>
#include <ostream>
#include "ros/serialization.h"
#include "ros/builtin_message_traits.h"
#include "ros/message_operations.h"
#include "ros/time.h"

#include "ros/macros.h"

#include "ros/assert.h"


namespace head_tracking_soft_controller
{
template <class ContainerAllocator>
struct PanTilt_ {
  typedef PanTilt_<ContainerAllocator> Type;

  PanTilt_()
  : data()
  {
    data.assign(0.0);
  }

  PanTilt_(const ContainerAllocator& _alloc)
  : data()
  {
    data.assign(0.0);
  }

  typedef boost::array<double, 2>  _data_type;
  boost::array<double, 2>  data;


  ROS_DEPRECATED uint32_t get_data_size() const { return (uint32_t)data.size(); }
private:
  static const char* __s_getDataType_() { return "head_tracking_soft_controller/PanTilt"; }
public:
  ROS_DEPRECATED static const std::string __s_getDataType() { return __s_getDataType_(); }

  ROS_DEPRECATED const std::string __getDataType() const { return __s_getDataType_(); }

private:
  static const char* __s_getMD5Sum_() { return "a64ac68384ecd108c6beb460bc157ad2"; }
public:
  ROS_DEPRECATED static const std::string __s_getMD5Sum() { return __s_getMD5Sum_(); }

  ROS_DEPRECATED const std::string __getMD5Sum() const { return __s_getMD5Sum_(); }

private:
  static const char* __s_getMessageDefinition_() { return "float64[2] data\n\
\n\
"; }
public:
  ROS_DEPRECATED static const std::string __s_getMessageDefinition() { return __s_getMessageDefinition_(); }

  ROS_DEPRECATED const std::string __getMessageDefinition() const { return __s_getMessageDefinition_(); }

  ROS_DEPRECATED virtual uint8_t *serialize(uint8_t *write_ptr, uint32_t seq) const
  {
    ros::serialization::OStream stream(write_ptr, 1000000000);
    ros::serialization::serialize(stream, data);
    return stream.getData();
  }

  ROS_DEPRECATED virtual uint8_t *deserialize(uint8_t *read_ptr)
  {
    ros::serialization::IStream stream(read_ptr, 1000000000);
    ros::serialization::deserialize(stream, data);
    return stream.getData();
  }

  ROS_DEPRECATED virtual uint32_t serializationLength() const
  {
    uint32_t size = 0;
    size += ros::serialization::serializationLength(data);
    return size;
  }

  typedef boost::shared_ptr< ::head_tracking_soft_controller::PanTilt_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::head_tracking_soft_controller::PanTilt_<ContainerAllocator>  const> ConstPtr;
  boost::shared_ptr<std::map<std::string, std::string> > __connection_header;
}; // struct PanTilt
typedef  ::head_tracking_soft_controller::PanTilt_<std::allocator<void> > PanTilt;

typedef boost::shared_ptr< ::head_tracking_soft_controller::PanTilt> PanTiltPtr;
typedef boost::shared_ptr< ::head_tracking_soft_controller::PanTilt const> PanTiltConstPtr;


template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const  ::head_tracking_soft_controller::PanTilt_<ContainerAllocator> & v)
{
  ros::message_operations::Printer< ::head_tracking_soft_controller::PanTilt_<ContainerAllocator> >::stream(s, "", v);
  return s;}

} // namespace head_tracking_soft_controller

namespace ros
{
namespace message_traits
{
template<class ContainerAllocator> struct IsMessage< ::head_tracking_soft_controller::PanTilt_<ContainerAllocator> > : public TrueType {};
template<class ContainerAllocator> struct IsMessage< ::head_tracking_soft_controller::PanTilt_<ContainerAllocator>  const> : public TrueType {};
template<class ContainerAllocator>
struct MD5Sum< ::head_tracking_soft_controller::PanTilt_<ContainerAllocator> > {
  static const char* value() 
  {
    return "a64ac68384ecd108c6beb460bc157ad2";
  }

  static const char* value(const  ::head_tracking_soft_controller::PanTilt_<ContainerAllocator> &) { return value(); } 
  static const uint64_t static_value1 = 0xa64ac68384ecd108ULL;
  static const uint64_t static_value2 = 0xc6beb460bc157ad2ULL;
};

template<class ContainerAllocator>
struct DataType< ::head_tracking_soft_controller::PanTilt_<ContainerAllocator> > {
  static const char* value() 
  {
    return "head_tracking_soft_controller/PanTilt";
  }

  static const char* value(const  ::head_tracking_soft_controller::PanTilt_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator>
struct Definition< ::head_tracking_soft_controller::PanTilt_<ContainerAllocator> > {
  static const char* value() 
  {
    return "float64[2] data\n\
\n\
";
  }

  static const char* value(const  ::head_tracking_soft_controller::PanTilt_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator> struct IsFixedSize< ::head_tracking_soft_controller::PanTilt_<ContainerAllocator> > : public TrueType {};
} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

template<class ContainerAllocator> struct Serializer< ::head_tracking_soft_controller::PanTilt_<ContainerAllocator> >
{
  template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
  {
    stream.next(m.data);
  }

  ROS_DECLARE_ALLINONE_SERIALIZER;
}; // struct PanTilt_
} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::head_tracking_soft_controller::PanTilt_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const  ::head_tracking_soft_controller::PanTilt_<ContainerAllocator> & v) 
  {
    s << indent << "data[]" << std::endl;
    for (size_t i = 0; i < v.data.size(); ++i)
    {
      s << indent << "  data[" << i << "]: ";
      Printer<double>::stream(s, indent + "  ", v.data[i]);
    }
  }
};


} // namespace message_operations
} // namespace ros

#endif // HEAD_TRACKING_SOFT_CONTROLLER_MESSAGE_PANTILT_H

