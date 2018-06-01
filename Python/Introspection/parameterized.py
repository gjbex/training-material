class Parameter:

    def __init__(self, name, ptype, value):
        self._name = name
        self._type = ptype
        if ptype is type(value):
            self._value = value
        else:
            raise TypeError(f'value {value} is not of type {dtype}')

    @property
    def name(self):
        return self._name

    @property
    def type(self):
        return self._type

    @property
    def value(self):
        return self._value

    @value.setter
    def value(self, new_value):
        if self._type is type(new_value):
            self._value = new_value
        else:
            raise TypeError(f'value {new_value} is not of '
                            f'type {self._type.__name__}')

    def __str__(self):
        return f'{self.name} = {str(self.value)}'


class ParameterError(Exception):
    pass


class Parameterized:
    
    def has_parameter(self, name):
        return ('__parameters' in self.__dict__  and
                name in self.__dict__['__parameters'])

    def _add_parameter(self, parameter):
        if '__parameters' not in self.__dict__:
            self.__dict__['__parameters'] = dict()
        self.__dict__['__parameters'][parameter.name] = parameter

    def __getattr__(self, name):
        if self.has_parameter(name):
            return self.__dict__['__parameters'][name].value
        else:
            return self.__dict__[name]

    def __setattr__(self, name, value):
        if self.has_parameter(name):
            self.__dict__['__parameters'][name].value = value
        else:
            self.__dict__[name] = value

    def get_parameter(self, name):
        if self.has_parameter(name):
            return self.__dict__['__parameters'][name]
        else:
            raise ParameterError(f"'{self.__class__}' object has no "
                                 f"parameter '{name}'")

    @property
    def get_parameter_names(self):
        if hasattr(self, '__parameters'):
            return list(self.__dict__['__parameters'].keys())
