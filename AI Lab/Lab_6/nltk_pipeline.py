import nltk
from nltk.tokenize import word_tokenize, sent_tokenize
from nltk.stem import PorterStemmer, WordNetLemmatizer
from nltk import pos_tag
from nltk.corpus import wordnet, stopwords
from nltk.parse import RecursiveDescentParser
from nltk.grammar import CFG
from googletrans import Translator
import warnings
warnings.filterwarnings('ignore')

class NLTKPipeline:
    def __init__(self):
        self.stemmer = PorterStemmer()
        self.lemmatizer = WordNetLemmatizer()
        self.translator = Translator()
        self._download_nltk_data()
        
    def _download_nltk_data(self):
        """Ensure all required NLTK data is available"""
        required_data = [
            'punkt', 'punkt_tab', 'averaged_perceptron_tagger',
            'maxent_ne_chunker', 'words', 'wordnet', 'stopwords'
        ]
        
        for data in required_data:
            try:
                nltk.data.find(f'tokenizers/{data}' if data == 'punkt_tab' else data)
            except LookupError:
                print(f"Downloading {data}...")
                nltk.download(data, quiet=True)
    
    def simple_sent_tokenize(self, text):
        """Fallback sentence tokenizer if punkt fails"""
        return [s.strip() for s in text.split('.') if s.strip()]
    
    def simple_word_tokenize(self, text):
        """Fallback word tokenizer"""
        return text.split()
    
    def lexical_analysis(self, text):
        print("=== LEXICAL ANALYSIS ===")
        
        try:
            sentences = sent_tokenize(text)
            words = word_tokenize(text)
        except:
            print("Using fallback tokenizers...")
            sentences = self.simple_sent_tokenize(text)
            words = self.simple_word_tokenize(text)
        
        print("Sentences:", sentences)
        print("Words:", words)
        
        stems = [self.stemmer.stem(word) for word in words]
        lemmas = [self.lemmatizer.lemmatize(word) for word in words]
        
        print("Stems:", stems)
        print("Lemmas:", lemmas)
        
        return words, stems, lemmas
    
    def syntactic_analysis(self, words):
        print("\n=== SYNTACTIC ANALYSIS ===")
        
        try:
            pos_tags = pos_tag(words)
            print("POS Tags:", pos_tags)
        except:
            print("POS tagging not available")
            pos_tags = []
        
        # Simple grammar parsing
        grammar = CFG.fromstring("""
            S -> NP VP
            NP -> Det N | Det N PP | 'I'
            VP -> V NP | V PP
            PP -> P NP
            Det -> 'the' | 'a'
            N -> 'cat' | 'dog' | 'house' | 'park'
            V -> 'chased' | 'saw' | 'visited'
            P -> 'in' | 'with'
        """)
        
        parser = RecursiveDescentParser(grammar)
        sample_sentence = "I saw the cat in the house".split()
        
        print("Parse trees for 'I saw the cat in the house':")
        try:
            for tree in parser.parse(sample_sentence):
                print(tree)
        except:
            print("Parsing not available")
        
        return pos_tags
    
    def semantic_analysis(self, text, words):
        print("\n=== SEMANTIC ANALYSIS ===")
        
        try:
            word = "bank"
            synsets = wordnet.synsets(word)
            print(f"Word senses for '{word}':")
            for i, synset in enumerate(synsets[:3]):
                print(f"{i+1}. {synset.definition()}")
        except:
            print("WordNet not available for semantic analysis")
            synsets = []
        
        return synsets
    
    def pragmatic_analysis(self, text):
        print("\n=== PRAGMATIC ANALYSIS ===")
        
        try:
            words = word_tokenize(text)
            pos_tags = pos_tag(words)
            
            # Simple named entity recognition (fallback)
            print("Named Entities (simplified):")
            entities = []
            for word, pos in pos_tags:
                if pos == 'NNP':  # Proper noun
                    entities.append(word)
                    print(f"  {word} - PROPER_NOUN")
            
        except:
            print("Named entity recognition not available")
            entities = []
        
        print("\nContext Analysis:")
        if "he" in text.lower() or "she" in text.lower() or "it" in text.lower():
            print("Pronouns detected - requires context for resolution")
        
        return entities
    
    def machine_translation(self, text, target_lang='es'):
        print("\n=== MACHINE TRANSLATION ===")
        
        try:
            translation = self.translator.translate(text, dest=target_lang)
            print(f"Original: {text}")
            print(f"Translation ({target_lang}): {translation.text}")
            return translation.text
        except:
            print("Translation service unavailable. Using fallback translation.")
            translation_dict = {
                'es': {'the': 'el', 'google': 'google', 'is': 'es', 'a': 'un', 'great': 'gran', 'company': 'empresa'},
                'fr': {'the': 'le', 'google': 'google', 'is': 'est', 'a': 'une', 'great': 'grande', 'company': 'entreprise'}
            }
            
            words = text.lower().split()
            translated_words = [translation_dict.get(target_lang, {}).get(word, word) 
                              for word in words]
            translated_text = ' '.join(translated_words)
            print(f"Fallback translation: {translated_text}")
            return translated_text
    
    def run_pipeline(self, text):
        print("INPUT TEXT:", text)
        print("\n" + "="*50)
        
        words, stems, lemmas = self.lexical_analysis(text)
        pos_tags = self.syntactic_analysis(words)
        semantic_results = self.semantic_analysis(text, words)
        pragmatic_results = self.pragmatic_analysis(text)
        translation = self.machine_translation(text, 'es')

if __name__ == "__main__":
    import sys
    
    if len(sys.argv) > 1:
        text = " ".join(sys.argv[1:])
    else:
        text = "John works at Google in California. He is a software engineer. The cat chased the mouse in the house."
    
    pipeline = NLTKPipeline()
    pipeline.run_pipeline(text)
