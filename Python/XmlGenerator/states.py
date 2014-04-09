class State(object):
    
    states = {}

    @staticmethod
    def get_state(state_name):
        global contents
        if state_name in contents and state_name != 'State':
            if state_name not in State.states:
                cls = type(state_name, (State,), {})
                State.states[state_name] = cls()
            return State.states[state_name]
        else:
            return None
            
    @classmethod
    def state_names(cls):
        global contents
        return contents

    @property
    def name(self):
        return self.__class__.__name__

    def get_next(token_str):
        for match in self._map:
            if match[0] == token_str:
                return match[1]
        return Error()

    def __str__(self):
        return self.name


class Doc_start(State):

    def __init__(self):
        self._map = [
            ('<?', [State.get_state('In_doc_info')]),
        ]


contents = [x for x in dir() if x != 'State' and not x.startswith('_')]
