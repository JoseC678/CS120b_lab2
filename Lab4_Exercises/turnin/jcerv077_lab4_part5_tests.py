tests = [ 
    {'description': 'PressPA0  => PORTC: 0x08 ',
    'steps': [ 
                {'inputs': [('PINA',0x04)], 'iterations': 1  },
                {'inputs': [('PINA',0x00)], 'iterations': 1 },
                {'inputs': [('PINA',0x01)], 'iterations': 1},
                {'inputs': [('PINA',0x00)], 'iterations': 1 },
                {'inputs': [('PINA',0x02)], 'iterations': 1 },
                {'inputs': [('PINA',0x00)], 'iterations': 1},
                 {'inputs': [('PINA',0x01)], 'iterations': 1 },
                 {'inputs': [('PINA',0x00)], 'iterations': 1 },
                 {'inputs': [('PINA',0x80)], 'iterations': 1 },




                 ],
    'expected': [('PORTB',0x00)],
    },








    ]

            
    