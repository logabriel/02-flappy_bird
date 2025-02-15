### Changelog 2025/02/14

### Clase PlayingState
    - Se agregó el atributo: current_strategy

    - Aclaración: Ahora este estado contiene el atributo current_strategy que valiéndose del patrón strategy es capaz de manejar los modos de juego difícil (HardMode) o normal (NormalMode). Los métodos update(), handle_inputs() y render() llaman simplemente a los métodos homónimos dependiendo del modo de juego.

### Clase Bird
    - Se agregaron los métodos: add_point() para marcar un punto cada vez que el ave cruza un par de troncos.

        get_score()             retorna los puntos.

        move_right()            movimiento hacia la derecha.

        move_left()             movimiento hacia la izquierda.

        stop_move()             detiene el movimiento.

        moving()                encapsula la funcionalidad para mover el ave horizontalmente.

        activate_power_up()     marca al ave cuando toma un power up.

        deactivate_power_up()   desmarca al ave cuando termina el tiempo del power up.

        get_intangible()        retorna el estado de intangible del ave.

    - Se agregaron los atributos: 
        vx : float 
        score : int 
        intangible : bool 
        timer_intangible : float

    - Aclaración: 
        Ahora el ave puede moverse horizontalmente, tomar un power_up y los puntos al cruzar la brecha de los pares de troncos se almacenan en la clase Bird.

### Clase Log
    - Aclaración: 
        Ahora es una clase padre de la que derivan las clases MovingLog para los troncos que abren y cierran la brecha en el modo difícil y StaticLog para los troncos normales.

### Clase LogPair
    - El constructor ahora recibe, aparte de su posición x e y, los troncos top y bottom.

    - Se agregaron los métodos: move_limiter() is_gap_closed() determinan cuándo la brecha está completamente cerrada, detectando colisiones en los pares de troncos para decidir si deben abrir o cerrar la brecha.

### Clase World
    - Se agregaron los métodos: 
        set_game_mode() define el modo de juego normal o difícil.

        activate_power_up() si el ave colisiona con el power up lo hace desaparecer.

    - Se agregaron los atributos: 
    power_up_factory    Factory de power up. 
    power_ups           lista de power up en la escena. game_mode

### Nuevas Clases:
### MovingLog
    - Aclaración: 
        Es la clase utilizada para instanciar los troncos que abren y cierran la brecha.

### StaticLog
    - Aclaración: 
        Clase utilizada para instanciar los troncos normales.

### PowerUp
    - Aclaración: 
        Clase utilizada para instanciar los power up en el modo de juego difícil.

### BaseStrategy
    - Aclaración: 
        Clase base para los modos de juego.

### NormalMode
    - Aclaración: 
        Encapsula toda la funcionalidad para el modo de juego normal. Anteriormente, este trabajo lo hacía el estado PlayingState.

### HardMode
    - Aclaración: 
        Encapsula toda la funcionalidad para el modo de juego difícil.