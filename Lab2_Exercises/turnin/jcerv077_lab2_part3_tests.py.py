tests = [ {'description': 'PA0: 0x01  => PORTC: 0x01',
    'steps': [ {'inputs': [('PINA',0x01)], 'iterations': 5 } ],
    'expected': [('PORTC',0x03)],
    },
    {'description': 'PA0=1 && PA1=1  => PORTC: 0x02',
    'steps': [ {'inputs': [('PINA',0x03)], 'iterations': 5 } ],
    'expected': [('PORTC',0x02)],
    },
    {'description': 'PA0=1 && PA1=1 && PA2=1 && PA3=1  => PORTC: 0x80',
    'steps': [ {'inputs': [('PINA',0x0F)], 'iterations': 5 } ],
    'expected': [('PORTC',0x80)],
    },
    ]
#watch = ['PORTB']
