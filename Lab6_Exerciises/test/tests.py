tests = [ 
    {'description': 'no PRess  => PORTC: 0x07 ',
    'steps': [ {'inputs': [('PINA',0xFF)], 'iterations': 1 },
                 ],
    'expected': [('PORTB',0x07)],
    },


    {'description': 'Press Once ',
    'steps': [ {'inputs': [('PINA',0xFE)], 'iterations': 2 },
                {'inputs': [('PINA',0xFE)], 'iterations': 2 },
                 ],
    'expected': [('PORTB',0x08)],
    },
    
  {'description': '3 press  ',
    'steps': [ {'inputs': [('PINA',0xFE)], 'iterations': 2 },
                {'inputs': [('PINA',0xFE)], 'iterations': 2 },
                 {'inputs': [('PINA',0xFF)], 'iterations': 2 },
                  {'inputs': [('PINA',0xFE)], 'iterations': 2 },
                 ],
    'expected': [('PORTB',0x09)],
    },


  #{'description': 'PressPA0  => PORTC: 0x08 ',
   # 'steps': [ {'inputs': [('PINA',0x00)], 'iterations': 2 },
    #            {'inputs': [('PINA',0x02)], 'iterations': 2 },
     #            {'inputs': [('PINA',0x02)], 'iterations': 2 },
      #            {'inputs': [('PINA',0x02)], 'iterations': 2 },
       #           {'inputs': [('PINA',0x02)], 'iterations': 2 },
        #         {'inputs': [('PINA',0x02)], 'iterations': 2 },
         #         {'inputs': [('PINA',0x02)], 'iterations': 2 },
          #       ],
  #  'expected': [('PORTC',0x06)],
   # },



    ]

    