tests = [ {'description': 'PND=0x46,B0=0  => PORTB: 0x02 ',
    'steps': [ {'inputs': [('PIND',0x46)], 'iterations': 1 },
                {'inputs': [('PINB',0x00)], 'iterations': 1 },
                 ],
    'expected': [('PORTB',0x02)],
    },

    {'description': 'PND=0x45,B0=0  => PORTB: 0x02 ',
    'steps': [ {'inputs': [('PIND',0x45)], 'iterations': 1 },
                {'inputs': [('PINB',0x00)], 'iterations': 1 },
                 ],
    'expected': [('PORTB',0x02)],
    },

        {'description': 'PND=0x00,B0=0  => PORTB: 0x00 ',
    'steps': [ {'inputs': [('PIND',0x00)], 'iterations': 1 },
                {'inputs': [('PINB',0x00)], 'iterations': 1 },
                 ],
    'expected': [('PORTB',0x00)],
    },

    
        {'description': 'PND=0x23,B0=0  =< PORTB: 0x02 ',
    'steps': [ {'inputs': [('PIND',0x23)], 'iterations': 1 },
                {'inputs': [('PINB',0x00)], 'iterations': 1 },
                 ],
    'expected': [('PORTB',0x02)],
    },

            {'description': 'PND=0x00,B0=0  =>  PORTB: 0x02 ',
    'steps': [ {'inputs': [('PIND',0x80)], 'iterations': 1 },
                {'inputs': [('PINB',0x00)], 'iterations': 1 },
                 ],
    'expected': [('PORTB',0x02)],
    },





    ]