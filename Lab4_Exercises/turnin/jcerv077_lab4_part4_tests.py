tests = [ 
    {'description': 'PressPA0  => PORTC: 0x08 ',
    'steps': [ 
                {'inputs': [('PINA',0x04)], 'iterations': 5  },
                {'inputs': [('PINA',0x00)], 'iterations': 5 },
                {'inputs': [('PINA',0x02)], 'iterations': 5 },
                 {'inputs': [('PINA',0x00)], 'iterations': 5 },
                {'inputs': [('PINA',0x04)], 'iterations': 5  },
                {'inputs': [('PINA',0x00)], 'iterations': 5 },
                {'inputs': [('PINA',0x02)], 'iterations': 5 },
                 {'inputs': [('PINA',0x00)], 'iterations': 5 },


                 ],
    'expected': [('PORTB',0x00)],
    },





    {'description': 'PressPA0  => PORTC: 0x08 ',
    'steps': [ {'inputs': [('PINA',0x00)], 'iterations': 1  }, 
                {'inputs': [('PINA',0x4)], 'iterations': 1 },
                {'inputs': [('PINA',0x0)], 'iterations': 1 },
                {'inputs': [('PINA',0x4)], 'iterations': 1 },

                 ],
    'expected': [('PORTB',0x00)],
    },



    ]

            
    