tests = [ 
            {'description': 'do nothing ,B0=0  => PORTB: 0x02 ',
    'steps': [ {'inputs': [('PINA',0x00)], 'iterations': 1 },

                 ],
    'expected': [('PORTB',0x01)],
    },

    
    {'description': 'Press/release/press/release,B0=0  => PORTB: 0x02 ',
    'steps': [ {'inputs': [('PINA',0x01)], 'iterations': 5,'expected': [('PORTB',0x02)], },
               {'inputs': [('PINA',0x00)], 'iterations': 5, 'expected': [('PORTB',0x02)],  },
               {'inputs': [('PINA',0x01)], 'iterations': 5,'expected': [('PORTB',0x01)], },
             {'inputs': [('PINA',0x00)], 'iterations': 5,'expected': [('PORTB',0x01)], },
                 ],
    'expected': [('PORTB',0x01)],
    },


        {'description': 'Press/release,B0=0  => PORTB: 0x02 ',
    'steps': [ {'inputs': [('PINA',0x01)], 'iterations': 5,'expected': [('PORTB',0x02)], },
               {'inputs': [('PINA',0x00)], 'iterations': 5, 'expected': [('PORTB',0x02)],  },
                 ],
    'expected': [('PORTB',0x02)],
    },





    ]