tests = [ 
    {'description': 'PressPA0  => PORTC: 0x08 ',
    'steps': [ {'inputs': [('PINA',0x00)], 'iterations': 1 },
                 ],
    'expected': [('PORTC',0x07)],
    },


    {'description': 'PressPA0  => PORTC: 0x08 ',
    'steps': [ {'inputs': [('PINA',0x01)], 'iterations': 2 },
                {'inputs': [('PINA',0x01)], 'iterations': 2 },
                 ],
    'expected': [('PORTC',0x08)],
    },
    
  {'description': 'PressPA0  => PORTC: 0x08 ',
    'steps': [ {'inputs': [('PINA',0x01)], 'iterations': 2 },
                {'inputs': [('PINA',0x01)], 'iterations': 2 },
                 {'inputs': [('PINA',0x01)], 'iterations': 2 },
                  {'inputs': [('PINA',0x01)], 'iterations': 2 },
                 ],
    'expected': [('PORTC',0x08)],
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

    