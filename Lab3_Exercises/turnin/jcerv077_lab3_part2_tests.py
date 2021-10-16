tests = [ {'description': 'PNA=0x71,  => PORTC: 0x60 = 96',
    'steps': [ {'inputs': [('PINA',0x71)], 'iterations': 1 },
                 ],
    'expected': [('PORTC',0x60)],
    },

    {'description': 'PNA=0x02,  => PORTC: 0x60 = 96',
    'steps': [ {'inputs': [('PINA',0x02)], 'iterations': 1 },
                 ],
    'expected': [('PORTC',0x60)],
    },

    {'description': 'PNA=0x03,  => PORTC: 0x70 = 112',
    'steps': [ {'inputs': [('PINA',0x03)], 'iterations': 1 },
                 ],
    'expected': [('PORTC',0x70)],
    },

    {'description': 'PNA=0x04,  => PORTC: 0x70 = 112',
    'steps': [ {'inputs': [('PINA',0x03)], 'iterations': 1 },
                 ],
    'expected': [('PORTC',0x70)],
    },

    {'description': 'PNA=0x013,  => PORTC: 0x3F = 63',
    'steps': [ {'inputs': [('PINA',0x0E)], 'iterations': 1 },
                 ],
    'expected': [('PORTC',0x3F)],
    },

    {'description': 'PNA=0x00,  => PORTC: 0x40 = 64',
    'steps': [ {'inputs': [('PINA',0x00)], 'iterations': 1 },
                 ],
    'expected': [('PORTC',0x40)],
    },

    {'description': 'PNA=0x30,  => PORTC: 0x80 = 128',
    'steps': [ {'inputs': [('PINA',0x30)], 'iterations': 1 },
                 ],
    'expected': [('PORTC',0x80)],
    },




    ]


