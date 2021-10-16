tests = [ {'description': 'PNA=0x71,  => PORTC: 0x60 = 96',
    'steps': [ {'inputs': [('PINA', 0xFF)], 'iterations': 1 },
                 ],
    'expected': [('PORTC',0x40)],
    },

    {'description': 'PNA=0x02,  => PORTC: 0x60 = 96',
    'steps': [ {'inputs': [('PINA', 0xFD)], 'iterations': 1 },
                 ],
    'expected': [('PORTC',0x60)],
    },

    {'description': 'PNA=0x03,  => PORTC: 0x70 = 112',
    'steps': [ {'inputs': [('PINA',0xFC)], 'iterations': 1 },
                 ],
    'expected': [('PORTC',0x70)],
    },

    {'description': 'PNA=0x04,  => PORTC: 0x70 = 112',
    'steps': [ {'inputs': [('PINA',0xFC)], 'iterations': 1 },
                 ],
    'expected': [('PORTC',0x70)],
    },

    {'description': 'PNA=0x013,  => PORTC: 0x3F = 63',
    'steps': [ {'inputs': [('PINA',0xF2)], 'iterations': 1 },
                 ],
    'expected': [('PORTC',0x3F)],
    },

    {'description': 'PNA=0x00,  => PORTC: 0x40 = 64',
    'steps': [ {'inputs': [('PINA',0xFF)], 'iterations': 1 },
                 ],
    'expected': [('PORTC',0x40)],
    },

    {'description': 'PNA=0x30,  => PORTC: 0x80 = 128',
    'steps': [ {'inputs': [('PINA',0xFF)], 'iterations': 1 },
                 ],
    'expected': [('PORTC',0x40)],
    },




    ]


