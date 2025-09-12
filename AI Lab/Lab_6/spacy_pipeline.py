import spacy
from googletrans import Translator
import warnings
warnings.filterwarnings('ignore')

class SpacyPipeline:
    def __init__(self):
        try:
            self.nlp = spacy.load("en_core_web_sm")
        except:
            print("Please download the spaCy model: python -m spacy download en_core_web_sm")
            raise
        self.translator = Translator()
    
    def lexical_analysis(self, text):
        print("=== LEXICAL ANALYSIS ===")
        
        doc = self.nlp(text)
        
        print("Sentences:")
        for i, sent in enumerate(doc.sents):
            print(f"  {i+1}. {sent.text}")
        
        print("\nTokens with morphological features:")
        for token in doc:
            print(f"  {token.text:15} | Lemma: {token.lemma_:10} | POS: {token.pos_:8} | Shape: {token.shape_:8}")
        
        return doc
    
    def syntactic_analysis(self, doc):
        print("\n=== SYNTACTIC ANALYSIS ===")
        
        print("POS Tags and Dependencies:")
        for token in doc:
            print(f"  {token.text:15} | POS: {token.pos_:8} | Dep: {token.dep_:12} | Head: {token.head.text}")
        
        return doc
    
    def semantic_analysis(self, doc):
        print("\n=== SEMANTIC ANALYSIS ===")
        
        word1 = doc[0] if len(doc) > 0 else self.nlp("cat")[0]
        word2 = self.nlp("dog")[0]
        
        similarity = word1.similarity(word2)
        print(f"Similarity between '{word1.text}' and '{word2.text}': {similarity:.3f}")
        
        return similarity
    
    def pragmatic_analysis(self, doc):
        print("\n=== PRAGMATIC ANALYSIS ===")
        
        print("Named Entities:")
        for ent in doc.ents:
            print(f"  {ent.text:20} | Label: {ent.label_:15} | Description: {spacy.explain(ent.label_)}")
        
        print("\nContext Analysis:")
        for token in doc:
            if token.pos_ == 'PRON':
                print(f"  Pronoun '{token.text}' detected - may refer to previous entities")
        
        return doc.ents
    
    def machine_translation(self, text, target_lang='es'):
        print("\n=== MACHINE TRANSLATION ===")
        
        try:
            translation = self.translator.translate(text, dest=target_lang)
            print(f"Original: {text}")
            print(f"Translation ({target_lang}): {translation.text}")
            return translation.text
        except:
            print("Translation service unavailable. Using fallback translation.")
            
            doc = self.nlp(text)
            translated_parts = []
            
            for token in doc:
                if token.text.lower() == "the": translated_parts.append("el" if target_lang == 'es' else "le")
                elif token.text.lower() == "cat": translated_parts.append("gato" if target_lang == 'es' else "chat")
                elif token.text.lower() == "dog": translated_parts.append("perro" if target_lang == 'es' else "chien")
                else: translated_parts.append(token.text)
            
            fallback_translation = " ".join(translated_parts)
            print(f"Fallback translation: {fallback_translation}")
            return fallback_translation
    
    def run_pipeline(self, text):
        print("INPUT TEXT:", text)
        print("\n" + "="*50)
        
        doc = self.nlp(text)
        
        lexical_doc = self.lexical_analysis(text)
        syntactic_doc = self.syntactic_analysis(doc)
        semantic_result = self.semantic_analysis(doc)
        pragmatic_results = self.pragmatic_analysis(doc)
        translation = self.machine_translation(text, 'fr')

if __name__ == "__main__":
    import sys
    
    if len(sys.argv) > 1:
        text = " ".join(sys.argv[1:])
    else:
        text = "Apple Inc. is planning to open a new store in Paris next month. The company CEO said they are excited about European expansion."
    
    pipeline = SpacyPipeline()
    pipeline.run_pipeline(text)
