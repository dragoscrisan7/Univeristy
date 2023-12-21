class FiniteAutomaton:
    def __init__(self, states, alphabet, transition_rules, initial_state, accepting_states):
        self.states = states
        self.alphabet = alphabet
        self.transition_rules = transition_rules
        self.current_state = initial_state
        self.accepting_states = accepting_states
        self.initial_state = initial_state

    def reset(self):
        self.current_state = self.initial_state

    def process_input(self, input_symbol):
        if input_symbol not in self.alphabet:
            raise ValueError(f"Input symbol '{input_symbol}' not in the alphabet.")

        if self.current_state not in self.states:
            raise ValueError(f"Invalid current state: {self.current_state}")

        if (self.current_state, input_symbol) in self.transition_rules:
            self.current_state = self.transition_rules[(self.current_state, input_symbol)]
        else:
            raise ValueError(f"No transition rule defined for current state {self.current_state} and input symbol {input_symbol}")

    def is_accepting(self):
        return self.current_state in self.accepting_states
