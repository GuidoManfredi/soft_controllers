"""autogenerated by genmsg_py from SM_SEGMENT_STR_ROS.msg. Do not edit."""
import roslib.message
import struct


class SM_SEGMENT_STR_ROS(roslib.message.Message):
  _md5sum = "1177219c152dc7e2bdf63b0d409cf1a3"
  _type = "pr2_soft_controller/SM_SEGMENT_STR_ROS"
  _has_header = False #flag to mark the presence of a Header object
  _full_text = """int32 lpId
int32 unused
float64 timeOnTraj
float64 time
float64 ic_a
float64 ic_v
float64 ic_x
float64 jerk


"""
  __slots__ = ['lpId','unused','timeOnTraj','time','ic_a','ic_v','ic_x','jerk']
  _slot_types = ['int32','int32','float64','float64','float64','float64','float64','float64']

  def __init__(self, *args, **kwds):
    """
    Constructor. Any message fields that are implicitly/explicitly
    set to None will be assigned a default value. The recommend
    use is keyword arguments as this is more robust to future message
    changes.  You cannot mix in-order arguments and keyword arguments.
    
    The available fields are:
       lpId,unused,timeOnTraj,time,ic_a,ic_v,ic_x,jerk
    
    @param args: complete set of field values, in .msg order
    @param kwds: use keyword arguments corresponding to message field names
    to set specific fields. 
    """
    if args or kwds:
      super(SM_SEGMENT_STR_ROS, self).__init__(*args, **kwds)
      #message fields cannot be None, assign default values for those that are
      if self.lpId is None:
        self.lpId = 0
      if self.unused is None:
        self.unused = 0
      if self.timeOnTraj is None:
        self.timeOnTraj = 0.
      if self.time is None:
        self.time = 0.
      if self.ic_a is None:
        self.ic_a = 0.
      if self.ic_v is None:
        self.ic_v = 0.
      if self.ic_x is None:
        self.ic_x = 0.
      if self.jerk is None:
        self.jerk = 0.
    else:
      self.lpId = 0
      self.unused = 0
      self.timeOnTraj = 0.
      self.time = 0.
      self.ic_a = 0.
      self.ic_v = 0.
      self.ic_x = 0.
      self.jerk = 0.

  def _get_types(self):
    """
    internal API method
    """
    return self._slot_types

  def serialize(self, buff):
    """
    serialize message into buffer
    @param buff: buffer
    @type  buff: StringIO
    """
    try:
      _x = self
      buff.write(_struct_2i6d.pack(_x.lpId, _x.unused, _x.timeOnTraj, _x.time, _x.ic_a, _x.ic_v, _x.ic_x, _x.jerk))
    except struct.error as se: self._check_types(se)
    except TypeError as te: self._check_types(te)

  def deserialize(self, str):
    """
    unpack serialized message in str into this message instance
    @param str: byte array of serialized message
    @type  str: str
    """
    try:
      end = 0
      _x = self
      start = end
      end += 56
      (_x.lpId, _x.unused, _x.timeOnTraj, _x.time, _x.ic_a, _x.ic_v, _x.ic_x, _x.jerk,) = _struct_2i6d.unpack(str[start:end])
      return self
    except struct.error as e:
      raise roslib.message.DeserializationError(e) #most likely buffer underfill


  def serialize_numpy(self, buff, numpy):
    """
    serialize message with numpy array types into buffer
    @param buff: buffer
    @type  buff: StringIO
    @param numpy: numpy python module
    @type  numpy module
    """
    try:
      _x = self
      buff.write(_struct_2i6d.pack(_x.lpId, _x.unused, _x.timeOnTraj, _x.time, _x.ic_a, _x.ic_v, _x.ic_x, _x.jerk))
    except struct.error as se: self._check_types(se)
    except TypeError as te: self._check_types(te)

  def deserialize_numpy(self, str, numpy):
    """
    unpack serialized message in str into this message instance using numpy for array types
    @param str: byte array of serialized message
    @type  str: str
    @param numpy: numpy python module
    @type  numpy: module
    """
    try:
      end = 0
      _x = self
      start = end
      end += 56
      (_x.lpId, _x.unused, _x.timeOnTraj, _x.time, _x.ic_a, _x.ic_v, _x.ic_x, _x.jerk,) = _struct_2i6d.unpack(str[start:end])
      return self
    except struct.error as e:
      raise roslib.message.DeserializationError(e) #most likely buffer underfill

_struct_I = roslib.message.struct_I
_struct_2i6d = struct.Struct("<2i6d")
