tests = [ 


    {'description': 'PressPA0  => PORTC: 0x08 ',
    'steps': [ {'inputs': [('PINA',0x00)], 'iterations': 2  }, 
                {'inputs': [('PINA',0x04)], 'iterations': 2 },
                {'inputs': [('PINA',0x02)], 'iterations': 2 },
                {'inputs': [('PINA',0x00)], 'iterations': 2 },

                 ],
    'expected': [('PORTB',0x00)],
    },



    ]

    

    