tests = [ {'description': 'PNA=0, PNB=35, PNC=85  => PORTD: 0x1E = ',
    'steps': [ {'inputs': [('PINA',0x00)], 'iterations': 5 },
                {'inputs': [('PINB',0x23)], 'iterations': 5 },
                {'inputs': [('PINC',0x55)], 'iterations': 5 }, ],
    'expected': [('PORTD',0x1E)],
    },

    {'description': 'PNA=PNB=PNC= 64  => PORTD: 0x31 = 49',
    'steps': [ {'inputs': [('PINA',0x40)], 'iterations': 5 },
                {'inputs': [('PINB',0x40)], 'iterations': 5 },
                {'inputs': [('PINC',0x40)], 'iterations': 5 }, ],
    'expected': [('PORTD',0x31)],
    },

    {'description': 'PNA=0, PNB=56, PNC=85  Total= 141  => PORTD: 0x22 = 34',
    'steps': [ {'inputs': [('PINA',0x00)], 'iterations': 5 },
                {'inputs': [('PINB',0x38)], 'iterations': 5 },
                {'inputs': [('PINC',0x55)], 'iterations': 5 }, ],
    'expected': [('PORTD',0x22)],
    },
    ]
#watch = ['PORTB']

