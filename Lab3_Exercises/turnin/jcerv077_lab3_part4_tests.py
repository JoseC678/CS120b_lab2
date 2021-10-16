tests = [ {'description': 'PNA=0xFF,  => PORTC: 0xF0, PORTB: 0x0F ',
    'steps': [ {'inputs': [('PINA',0xFF)], 'iterations': 1 },
                 ],
    'expected': [('PORTC',0xF0)],
    },

    {'description': 'PNA=0xFF,  => PORTC: 0xF0, PORTB: 0x0F ',
    'steps': [ {'inputs': [('PINA',0xFF)], 'iterations': 1 },
                 ],
    'expected': [('PORTB',0x0F)],
    },

        {'description': 'PNA=0x57,  => PORTC: 0x70',
    'steps': [ {'inputs': [('PINA',0x57)], 'iterations': 1 },
                 ],
    'expected': [('PORTC',0x70)],
    },

            {'description': 'PNA=0x57,  => PORTC: 0x05',
    'steps': [ {'inputs': [('PINA',0x57)], 'iterations': 1 },
                 ],
    'expected': [('PORTB',0x05)],
    },





    ]