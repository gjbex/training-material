'''
Module that implements a mix-in to provide parameter introspection to
derived classes.
'''

class Parameter:
    '''
    Class representing a parameter. A parameter has a name, a Python type
    and a value. The name and type of a paramter can be queried, but not
    modified. The value can be queried and changed at any time.
    '''

    def __init__(self, name, ptype, value):
        '''
        Constructor for a Parameter object.
            name: parameter's name, a string
            type: parameter value's type, a Python type
            value: parameter's value, should be of the specified type

        The constructor will raise a TypeError if the name is not a str,
        the type is not a Python type, and a ValueError if the value is
        not of the specified type.
        '''
        if type(name) is not str:
            raise TypeError('name should be a str')
        self._name = name
        if type(ptype) is not type:
            raise TypeError('type should be a Python type')
        self._type = ptype
        self._value = self._type(value)

    @property
    def name(self):
        '''
        Returns the parameter's name, a string.
        '''
        return self._name

    @property
    def type(self):
        '''
        Returns the parameter's type, a Python type.
        '''
        return self._type

    @property
    def value(self):
        '''
        Returns the parameter's value.
        '''
        return self._value

    @value.setter
    def value(self, new_value):
        '''
        Sets the parameter's value.
            value: new value for the parameter

        This method raises ValueError if the value is not of the
        parameter's type.
        '''
        self._value = self._type(new_value)

    def __str__(self):
        '''
        Returns a string representation of the parameter.
        '''
        return f'{self.name} = {str(self.value)}'


class ParameterError(Exception):
    '''
    Exception raised when a Parameterized object has no parameter with
    the specified name.
    '''

    pass


class Parameterized:
    '''
    Mix-in class that adds parameters to a class.  This should be done
    in the __init__ method of the derived class using the _add_parameter
    method. The values can be retrieved and modified at any time
    as if they were object attributes of the derived class.

    The class also has methods to retrieve the names of all the parameters,
    and a method to access the actual parameter objects.  The latter
    should be handled with care.
    '''
    
    def has_parameter(self, name):
        '''
        Returns True if the object has a parameter with the specified.
        name
            name: parameter's name
        '''
        return ('__parameters' in self.__dict__  and
                name in self.__dict__['__parameters'])

    def get_parameter_type(self, name):
        '''
        Returns the parameter's type.
            name: parameter's name

        Raises ParameterError when the object has no parameter with
        the given name.
        '''
        if self.has_parameter(name):
            return self.__dict__['__parameters'][name].type
        else:
            raise ParameterError(f"'{self.__class__}' object has no "
                                 f"parameter '{name}'")

    def get_parameter_value(self, name):
        '''
        Returns the parameter's value.
            name: parameter's name

        Raises ParameterError when the object has no parameter with
        the given name.
        '''
        if self.has_parameter(name):
            return self.__dict__['__parameters'][name].value
        else:
            raise ParameterError(f"'{self.__class__}' object has no "
                                 f"parameter '{name}'")

    def set_parameter_value(self, name, value):
        '''
        Sets the value of the given parameter.
            name: parameter's name
            value: new value for the parameter

        Raises a ParameterError when the object has no parameter with
        the given name, a ValueError when the value's type is not that of
        the parameter.
        '''
        if self.has_parameter(name):
            self.__dict__['__parameters'][name].value = value
        else:
            raise ParameterError(f"'{self.__class__}' object has no "
                                 f"parameter '{name}'")
    def _add_parameter(self, parameter):
        '''
        Adds a parameter to the given object, to be called from the
        __init__ method of the derived class.
            parameter: Parameter object
        '''
        if '__parameters' not in self.__dict__:
            self.__dict__['__parameters'] = {}
        self.__dict__['__parameters'][parameter.name] = parameter

    def __getattr__(self, name):
        '''
        Overrides default method to ensure that the object's parameters
        can be accessed as if they were object attributes of the derived
        class.
        '''
        if self.has_parameter(name):
            return self.__dict__['__parameters'][name].value
        else:
            return self.__dict__[name]

    def __setattr__(self, name, value):
        '''
        Overrides default method to ensure that the object's parameters
        can be set as if they were object attributes of the derived
        class.
        '''
        if self.has_parameter(name):
            self.__dict__['__parameters'][name].value = value
        else:
            self.__dict__[name] = value

    def _get_parameter(self, name):
        '''
        Returns the Parameter object with that name.
            name: name of the parameter to retrieve

        Raises a ParameterError if no parameter exists with the given
        name.

        This method should be treated with care.
        '''
        if self.has_parameter(name):
            return self.__dict__['__parameters'][name]
        else:
            raise ParameterError(f"'{self.__class__}' object has no "
                                 f"parameter '{name}'")

    @property
    def get_parameter_names(self):
        '''
        Returns a list with the names of the parameters defined for the
        object.
        '''
        if hasattr(self, '__parameters'):
            return list(self.__dict__['__parameters'].keys())
        else:
            return []
