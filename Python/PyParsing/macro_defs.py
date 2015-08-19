'''Module containing implementations of macros that
   can be used in macro-expansion texts.'''


def upper(text):
    '''convert argument to all uppercase'''
    return text.upper()


def lower(text):
    '''convert argument to all lowercase'''
    return text.lower()


def author():
    '''returns the author'''
    return 'Geert Jan Bex'
