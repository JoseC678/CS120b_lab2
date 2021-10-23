tests = [ 
    {'description': 'Cycle Throught the lights ',
    'steps': [ {'inputs': [('PINA',0x00)], 'iterations': 1, 'expected': [('PORTB',0x01)] },
                {'inputs': [('PINA',0x00)], 'iterations': 1, 'expected': [('PORTB',0x02)] },
                {'inputs': [('PINA',0x00)], 'iterations': 1, 'expected': [('PORTB',0x04)] },
                {'inputs': [('PINA',0x00)], 'iterations': 1, 'expected': [('PORTB',0x01)] },
                {'inputs': [('PINA',0x00)], 'iterations': 1, 'expected': [('PORTB',0x02)] },



                 ],
    'expected': [('PORTB',0x02)],
    },


    ]

    