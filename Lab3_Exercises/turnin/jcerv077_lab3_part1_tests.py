tests = [ {'description': 'PNA=PINB=0xFF,  => PORTC: 0x016 = 8',
    'steps': [ {'inputs': [('PINA',0xFF)], 'iterations': 1 },
                {'inputs': [('PINB',0xFF)], 'iterations': 1 }, ],
    'expected': [('PORTC',0x10)],
    },

    {'description': 'PNA=0xF0, PINAB=0x02  => PORTC: 0x05 = 5',
    'steps': [ {'inputs': [('PINA',0xF0)], 'iterations': 1 },
                {'inputs': [('PINB',0x01)], 'iterations': 1 }, ],
    'expected': [('PORTC',0x05)], 
    },

    {'description': 'PNA=0xF0, PINAB=0x02  => PORTC: 0x05 = 6',
    'steps': [ {'inputs': [('PINA',0xF0)], 'iterations': 1 },
                {'inputs': [('PINB',0x03)], 'iterations': 1 }, ],
    'expected': [('PORTC',0x06)], 
    },


    ]


