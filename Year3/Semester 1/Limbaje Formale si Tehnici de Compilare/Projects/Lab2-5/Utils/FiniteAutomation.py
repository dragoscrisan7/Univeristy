class FiniteAutomata:
    def __init__(self, fa_file_path):
        self.states = set()
        self.alphabet = set()
        self.transitions = []
        self.initial_state = None
        self.final_states = set()

        self.read_fa_from_file(fa_file_path)

    def read_fa_from_file(self, fa_file_path):
        with open(fa_file_path, 'r') as file:
            lines = file.readlines()

        current_section = None

        for line in lines:
            line = line.strip()

            if line.startswith('States'):
                current_section = 'states'
            elif line.startswith('Alphabet'):
                current_section = 'alphabet'
            elif line.startswith('Transitions'):
                current_section = 'transitions'
            elif line.startswith('Initial'):
                current_section = 'initial'
            elif line.startswith('Final'):
                current_section = 'final'
            elif line:
                if current_section == 'states':
                    self.states.add(line)
                elif current_section == 'alphabet':
                    self.alphabet.add(line)
                elif current_section == 'transitions':
                    parts = line.split('->')
                    if len(parts) == 2:
                        from_state, transition = parts[0].strip(), parts[1].strip()
                        symbol, to_state = transition.split()
                        self.transitions.append((from_state, symbol, to_state))
                elif current_section == 'initial':
                    self.initial_state = line
                elif current_section == 'final':
                    self.final_states.add(line)
