tests = [ {'description': 'PNA=0x01, 1 10 1000  => PORTC: 0x60 = 96',
    'steps': [ {'inputs': [('PINA',0x01)], 'iterations': 1 },
                 ],
    'expected': [('PORTC',0x60)],
    },

    {'description': 'PNA=0x02, 1 10 0000  => PORTC: 0x60 = 96',
    'steps': [ {'inputs': [('PINA',0x02)], 'iterations': 1 },
                 ],
    'expected': [('PORTC',0x60)],
    },

    {'description': 'PNA=0x03, 1 11 0000  => PORTC: 0x70 = 112',
    'steps': [ {'inputs': [('PINA',0x03)], 'iterations': 1 },
                 ],
    'expected': [('PORTC',0x70)],
    },

    {'description': 'PNA=0x04, 1 11 0000  => PORTC: 0x70 = 112',
    'steps': [ {'inputs': [('PINA',0x03)], 'iterations': 1 },
                 ],
    'expected': [('PORTC',0x70)],
    },

    {'description': 'PNA=0x0E,0 11 1111  => PORTC: 0x3F = 63',
    'steps': [ {'inputs': [('PINA',0x0E)], 'iterations': 1 },
                 ],
    'expected': [('PORTC',0x3F)],
    },

    {'description': 'PNA=0x00, 1 00 0000  => PORTC: 0x40 = 64',
    'steps': [ {'inputs': [('PINA',0x00)], 'iterations': 1 },
                 ],
    'expected': [('PORTC',0x40)],
    },


        {'description': 'PNA=0x30, 1 00 0000  => PORTC: 0x40 = 64',
    'steps': [ {'inputs': [('PINA',0x30)], 'iterations': 1 },
                 ],
    'expected': [('PORTC',0xC0)],
    },

            {'description': 'PNA=0x7F, 0 11 1111  => PORTC: 0x3F ',
    'steps': [ {'inputs': [('PINA',0x7F)], 'iterations': 1 },
                 ],
    'expected': [('PORTC',0x3F )],
    },




    ]