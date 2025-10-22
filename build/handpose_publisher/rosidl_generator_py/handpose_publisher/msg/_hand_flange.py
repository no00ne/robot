# generated from rosidl_generator_py/resource/_idl.py.em
# with input from handpose_publisher:msg/HandFlange.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import math  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_HandFlange(type):
    """Metaclass of message 'HandFlange'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
    }

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('handpose_publisher')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'handpose_publisher.msg.HandFlange')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__hand_flange
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__hand_flange
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__hand_flange
            cls._TYPE_SUPPORT = module.type_support_msg__msg__hand_flange
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__hand_flange

            from std_msgs.msg import Header
            if Header.__class__._TYPE_SUPPORT is None:
                Header.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class HandFlange(metaclass=Metaclass_HandFlange):
    """Message class 'HandFlange'."""

    __slots__ = [
        '_header',
        '_hand_id',
        '_frame_id',
        '_x',
        '_y',
        '_z',
        '_rx_millideg',
        '_ry_millideg',
        '_rz_millideg',
        '_pinch_strength',
    ]

    _fields_and_field_types = {
        'header': 'std_msgs/Header',
        'hand_id': 'int64',
        'frame_id': 'uint64',
        'x': 'double',
        'y': 'double',
        'z': 'double',
        'rx_millideg': 'int64',
        'ry_millideg': 'int64',
        'rz_millideg': 'int64',
        'pinch_strength': 'float',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.NamespacedType(['std_msgs', 'msg'], 'Header'),  # noqa: E501
        rosidl_parser.definition.BasicType('int64'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint64'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('int64'),  # noqa: E501
        rosidl_parser.definition.BasicType('int64'),  # noqa: E501
        rosidl_parser.definition.BasicType('int64'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        from std_msgs.msg import Header
        self.header = kwargs.get('header', Header())
        self.hand_id = kwargs.get('hand_id', int())
        self.frame_id = kwargs.get('frame_id', int())
        self.x = kwargs.get('x', float())
        self.y = kwargs.get('y', float())
        self.z = kwargs.get('z', float())
        self.rx_millideg = kwargs.get('rx_millideg', int())
        self.ry_millideg = kwargs.get('ry_millideg', int())
        self.rz_millideg = kwargs.get('rz_millideg', int())
        self.pinch_strength = kwargs.get('pinch_strength', float())

    def __repr__(self):
        typename = self.__class__.__module__.split('.')
        typename.pop()
        typename.append(self.__class__.__name__)
        args = []
        for s, t in zip(self.__slots__, self.SLOT_TYPES):
            field = getattr(self, s)
            fieldstr = repr(field)
            # We use Python array type for fields that can be directly stored
            # in them, and "normal" sequences for everything else.  If it is
            # a type that we store in an array, strip off the 'array' portion.
            if (
                isinstance(t, rosidl_parser.definition.AbstractSequence) and
                isinstance(t.value_type, rosidl_parser.definition.BasicType) and
                t.value_type.typename in ['float', 'double', 'int8', 'uint8', 'int16', 'uint16', 'int32', 'uint32', 'int64', 'uint64']
            ):
                if len(field) == 0:
                    fieldstr = '[]'
                else:
                    assert fieldstr.startswith('array(')
                    prefix = "array('X', "
                    suffix = ')'
                    fieldstr = fieldstr[len(prefix):-len(suffix)]
            args.append(s[1:] + '=' + fieldstr)
        return '%s(%s)' % ('.'.join(typename), ', '.join(args))

    def __eq__(self, other):
        if not isinstance(other, self.__class__):
            return False
        if self.header != other.header:
            return False
        if self.hand_id != other.hand_id:
            return False
        if self.frame_id != other.frame_id:
            return False
        if self.x != other.x:
            return False
        if self.y != other.y:
            return False
        if self.z != other.z:
            return False
        if self.rx_millideg != other.rx_millideg:
            return False
        if self.ry_millideg != other.ry_millideg:
            return False
        if self.rz_millideg != other.rz_millideg:
            return False
        if self.pinch_strength != other.pinch_strength:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def header(self):
        """Message field 'header'."""
        return self._header

    @header.setter
    def header(self, value):
        if __debug__:
            from std_msgs.msg import Header
            assert \
                isinstance(value, Header), \
                "The 'header' field must be a sub message of type 'Header'"
        self._header = value

    @builtins.property
    def hand_id(self):
        """Message field 'hand_id'."""
        return self._hand_id

    @hand_id.setter
    def hand_id(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'hand_id' field must be of type 'int'"
            assert value >= -9223372036854775808 and value < 9223372036854775808, \
                "The 'hand_id' field must be an integer in [-9223372036854775808, 9223372036854775807]"
        self._hand_id = value

    @builtins.property
    def frame_id(self):
        """Message field 'frame_id'."""
        return self._frame_id

    @frame_id.setter
    def frame_id(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'frame_id' field must be of type 'int'"
            assert value >= 0 and value < 18446744073709551616, \
                "The 'frame_id' field must be an unsigned integer in [0, 18446744073709551615]"
        self._frame_id = value

    @builtins.property
    def x(self):
        """Message field 'x'."""
        return self._x

    @x.setter
    def x(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'x' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'x' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._x = value

    @builtins.property
    def y(self):
        """Message field 'y'."""
        return self._y

    @y.setter
    def y(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'y' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'y' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._y = value

    @builtins.property
    def z(self):
        """Message field 'z'."""
        return self._z

    @z.setter
    def z(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'z' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'z' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._z = value

    @builtins.property
    def rx_millideg(self):
        """Message field 'rx_millideg'."""
        return self._rx_millideg

    @rx_millideg.setter
    def rx_millideg(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'rx_millideg' field must be of type 'int'"
            assert value >= -9223372036854775808 and value < 9223372036854775808, \
                "The 'rx_millideg' field must be an integer in [-9223372036854775808, 9223372036854775807]"
        self._rx_millideg = value

    @builtins.property
    def ry_millideg(self):
        """Message field 'ry_millideg'."""
        return self._ry_millideg

    @ry_millideg.setter
    def ry_millideg(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'ry_millideg' field must be of type 'int'"
            assert value >= -9223372036854775808 and value < 9223372036854775808, \
                "The 'ry_millideg' field must be an integer in [-9223372036854775808, 9223372036854775807]"
        self._ry_millideg = value

    @builtins.property
    def rz_millideg(self):
        """Message field 'rz_millideg'."""
        return self._rz_millideg

    @rz_millideg.setter
    def rz_millideg(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'rz_millideg' field must be of type 'int'"
            assert value >= -9223372036854775808 and value < 9223372036854775808, \
                "The 'rz_millideg' field must be an integer in [-9223372036854775808, 9223372036854775807]"
        self._rz_millideg = value

    @builtins.property
    def pinch_strength(self):
        """Message field 'pinch_strength'."""
        return self._pinch_strength

    @pinch_strength.setter
    def pinch_strength(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'pinch_strength' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'pinch_strength' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._pinch_strength = value
