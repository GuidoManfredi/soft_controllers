"""autogenerated by genmsg_py from SoftMoveBaseGoal.msg. Do not edit."""
import roslib.message
import struct

import pr2_soft_controller.msg

class SoftMoveBaseGoal(roslib.message.Message):
  _md5sum = "d5522a248bbf08e0a75f1902c082cf61"
  _type = "soft_move_base/SoftMoveBaseGoal"
  _has_header = False #flag to mark the presence of a Header object
  _full_text = """# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======
#goal definition
pr2_soft_controller/SM_TRAJ_STR_ROS traj

================================================================================
MSG: pr2_soft_controller/SM_TRAJ_STR_ROS
int32 trajId
int32 nbAxis
float64 timePreserved
float64[] qStart
float64[] qGoal
float64[] jmax
float64[] amax
float64[] vmax
SM_TRAJ_AXIS_STR_ROS[] traj

================================================================================
MSG: pr2_soft_controller/SM_TRAJ_AXIS_STR_ROS
int32 nbSeg
int32 unsused
SM_SEGMENT_STR_ROS[] seg


================================================================================
MSG: pr2_soft_controller/SM_SEGMENT_STR_ROS
int32 lpId
int32 unused
float64 timeOnTraj
float64 time
float64 ic_a
float64 ic_v
float64 ic_x
float64 jerk


"""
  __slots__ = ['traj']
  _slot_types = ['pr2_soft_controller/SM_TRAJ_STR_ROS']

  def __init__(self, *args, **kwds):
    """
    Constructor. Any message fields that are implicitly/explicitly
    set to None will be assigned a default value. The recommend
    use is keyword arguments as this is more robust to future message
    changes.  You cannot mix in-order arguments and keyword arguments.
    
    The available fields are:
       traj
    
    @param args: complete set of field values, in .msg order
    @param kwds: use keyword arguments corresponding to message field names
    to set specific fields. 
    """
    if args or kwds:
      super(SoftMoveBaseGoal, self).__init__(*args, **kwds)
      #message fields cannot be None, assign default values for those that are
      if self.traj is None:
        self.traj = pr2_soft_controller.msg.SM_TRAJ_STR_ROS()
    else:
      self.traj = pr2_soft_controller.msg.SM_TRAJ_STR_ROS()

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
      buff.write(_struct_2id.pack(_x.traj.trajId, _x.traj.nbAxis, _x.traj.timePreserved))
      length = len(self.traj.qStart)
      buff.write(_struct_I.pack(length))
      pattern = '<%sd'%length
      buff.write(struct.pack(pattern, *self.traj.qStart))
      length = len(self.traj.qGoal)
      buff.write(_struct_I.pack(length))
      pattern = '<%sd'%length
      buff.write(struct.pack(pattern, *self.traj.qGoal))
      length = len(self.traj.jmax)
      buff.write(_struct_I.pack(length))
      pattern = '<%sd'%length
      buff.write(struct.pack(pattern, *self.traj.jmax))
      length = len(self.traj.amax)
      buff.write(_struct_I.pack(length))
      pattern = '<%sd'%length
      buff.write(struct.pack(pattern, *self.traj.amax))
      length = len(self.traj.vmax)
      buff.write(_struct_I.pack(length))
      pattern = '<%sd'%length
      buff.write(struct.pack(pattern, *self.traj.vmax))
      length = len(self.traj.traj)
      buff.write(_struct_I.pack(length))
      for val1 in self.traj.traj:
        _x = val1
        buff.write(_struct_2i.pack(_x.nbSeg, _x.unsused))
        length = len(val1.seg)
        buff.write(_struct_I.pack(length))
        for val2 in val1.seg:
          _x = val2
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
      if self.traj is None:
        self.traj = pr2_soft_controller.msg.SM_TRAJ_STR_ROS()
      end = 0
      _x = self
      start = end
      end += 16
      (_x.traj.trajId, _x.traj.nbAxis, _x.traj.timePreserved,) = _struct_2id.unpack(str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      pattern = '<%sd'%length
      start = end
      end += struct.calcsize(pattern)
      self.traj.qStart = struct.unpack(pattern, str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      pattern = '<%sd'%length
      start = end
      end += struct.calcsize(pattern)
      self.traj.qGoal = struct.unpack(pattern, str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      pattern = '<%sd'%length
      start = end
      end += struct.calcsize(pattern)
      self.traj.jmax = struct.unpack(pattern, str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      pattern = '<%sd'%length
      start = end
      end += struct.calcsize(pattern)
      self.traj.amax = struct.unpack(pattern, str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      pattern = '<%sd'%length
      start = end
      end += struct.calcsize(pattern)
      self.traj.vmax = struct.unpack(pattern, str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      self.traj.traj = []
      for i in range(0, length):
        val1 = pr2_soft_controller.msg.SM_TRAJ_AXIS_STR_ROS()
        _x = val1
        start = end
        end += 8
        (_x.nbSeg, _x.unsused,) = _struct_2i.unpack(str[start:end])
        start = end
        end += 4
        (length,) = _struct_I.unpack(str[start:end])
        val1.seg = []
        for i in range(0, length):
          val2 = pr2_soft_controller.msg.SM_SEGMENT_STR_ROS()
          _x = val2
          start = end
          end += 56
          (_x.lpId, _x.unused, _x.timeOnTraj, _x.time, _x.ic_a, _x.ic_v, _x.ic_x, _x.jerk,) = _struct_2i6d.unpack(str[start:end])
          val1.seg.append(val2)
        self.traj.traj.append(val1)
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
      buff.write(_struct_2id.pack(_x.traj.trajId, _x.traj.nbAxis, _x.traj.timePreserved))
      length = len(self.traj.qStart)
      buff.write(_struct_I.pack(length))
      pattern = '<%sd'%length
      buff.write(self.traj.qStart.tostring())
      length = len(self.traj.qGoal)
      buff.write(_struct_I.pack(length))
      pattern = '<%sd'%length
      buff.write(self.traj.qGoal.tostring())
      length = len(self.traj.jmax)
      buff.write(_struct_I.pack(length))
      pattern = '<%sd'%length
      buff.write(self.traj.jmax.tostring())
      length = len(self.traj.amax)
      buff.write(_struct_I.pack(length))
      pattern = '<%sd'%length
      buff.write(self.traj.amax.tostring())
      length = len(self.traj.vmax)
      buff.write(_struct_I.pack(length))
      pattern = '<%sd'%length
      buff.write(self.traj.vmax.tostring())
      length = len(self.traj.traj)
      buff.write(_struct_I.pack(length))
      for val1 in self.traj.traj:
        _x = val1
        buff.write(_struct_2i.pack(_x.nbSeg, _x.unsused))
        length = len(val1.seg)
        buff.write(_struct_I.pack(length))
        for val2 in val1.seg:
          _x = val2
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
      if self.traj is None:
        self.traj = pr2_soft_controller.msg.SM_TRAJ_STR_ROS()
      end = 0
      _x = self
      start = end
      end += 16
      (_x.traj.trajId, _x.traj.nbAxis, _x.traj.timePreserved,) = _struct_2id.unpack(str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      pattern = '<%sd'%length
      start = end
      end += struct.calcsize(pattern)
      self.traj.qStart = numpy.frombuffer(str[start:end], dtype=numpy.float64, count=length)
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      pattern = '<%sd'%length
      start = end
      end += struct.calcsize(pattern)
      self.traj.qGoal = numpy.frombuffer(str[start:end], dtype=numpy.float64, count=length)
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      pattern = '<%sd'%length
      start = end
      end += struct.calcsize(pattern)
      self.traj.jmax = numpy.frombuffer(str[start:end], dtype=numpy.float64, count=length)
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      pattern = '<%sd'%length
      start = end
      end += struct.calcsize(pattern)
      self.traj.amax = numpy.frombuffer(str[start:end], dtype=numpy.float64, count=length)
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      pattern = '<%sd'%length
      start = end
      end += struct.calcsize(pattern)
      self.traj.vmax = numpy.frombuffer(str[start:end], dtype=numpy.float64, count=length)
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      self.traj.traj = []
      for i in range(0, length):
        val1 = pr2_soft_controller.msg.SM_TRAJ_AXIS_STR_ROS()
        _x = val1
        start = end
        end += 8
        (_x.nbSeg, _x.unsused,) = _struct_2i.unpack(str[start:end])
        start = end
        end += 4
        (length,) = _struct_I.unpack(str[start:end])
        val1.seg = []
        for i in range(0, length):
          val2 = pr2_soft_controller.msg.SM_SEGMENT_STR_ROS()
          _x = val2
          start = end
          end += 56
          (_x.lpId, _x.unused, _x.timeOnTraj, _x.time, _x.ic_a, _x.ic_v, _x.ic_x, _x.jerk,) = _struct_2i6d.unpack(str[start:end])
          val1.seg.append(val2)
        self.traj.traj.append(val1)
      return self
    except struct.error as e:
      raise roslib.message.DeserializationError(e) #most likely buffer underfill

_struct_I = roslib.message.struct_I
_struct_2i6d = struct.Struct("<2i6d")
_struct_2id = struct.Struct("<2id")
_struct_2i = struct.Struct("<2i")
