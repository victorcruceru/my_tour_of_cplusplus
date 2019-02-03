/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * Victor Cruceru wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return.
 * ----------------------------------------------------------------------------
 */

/*
 * Description: std::shared_ptr examples
 */ 
#include <cstddef>
#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <memory> // std::make_shared
#include <locale>

#include <io.h>
#include <fcntl.h>

class Poem{
  public:
    using lyrics_t = std::vector<std::wstring>;

  private:
    std::wstring title_ = L"";
    std::wstring author_ = L"";
    lyrics_t lyrics_ = {};

  public:
    Poem(){
      std::wcout << "Calling *Default* Constructor" <<  std::hex 
                 << ", this = " << this << std::endl;
    }

    Poem(const std::wstring& title, const std::wstring& author, 
         const lyrics_t& lyrics): 
        title_{title}, author_{author}, lyrics_{lyrics}{
      std::wcout << "Calling Constructor for: " << title <<", " << author
                 <<  std::hex << ", this = " << this << std::endl;

    } 
     
    Poem(const Poem& other): title_{other.title_}, author_{other.author_}, \
                              lyrics_{other.lyrics_} {
      std::wcout << "Calling *Copy* Constructor" <<  std::hex 
                 << ", this = " << this << std::endl;

    } 

    Poem(const Poem&& other) noexcept:  
      title_{std::move(other.title_)}, 
      author_{std::move(other.author_)}, 
      lyrics_{std::move(other.lyrics_)}  {
      std::wcout << "Calling *Move* Constructor" <<  std::hex 
                 << ", this = " << this << std::endl;
     
    } 


    Poem& operator=(const Poem& other){
      std::wcout << "Calling assignment operator" << std::hex 
                 << ", this = " << this << std::endl;
      title_ = other.title_;
      author_ = other.author_;
      lyrics_ = other.lyrics_;
      return (*this);
    } 

    Poem& operator=(Poem&& other){
      std::wcout << "Calling *move* assignment operator" <<  std::hex 
                 << ", this = " << this << std::endl;
      title_ = std::move(other.title_);
      author_ = std::move(other.author_);
      lyrics_ = std::move(other.lyrics_);
      return (*this);
    } 

    ~Poem() noexcept {
      std::wcout << "Calling Destructor for: " << title_ << ", " << author_ 
                 << std::hex << ", this = " << this << std::endl;
    } 
    
    const std::wstring& get_title(void) const{
      return this->title_;
    }

    const std::wstring& get_author(void) const{
      return this->author_;
    }  

    const lyrics_t& get_lyrics(void) const {
      return this->lyrics_;
    }

    void set_author(const std::wstring& author){
      this->author_= author;
    }

};

int main(){
  //std::locale::global(std::locale("en_US.utf8"));
  //std::wcout.imbue(std::locale());

  
  
  //_setmode(_fileno(stdout), _O_U16TEXT);

  Poem p1 {
    L"Venus and Adonis",
    L"William Shakespeare",    
    {
      L"EVEN as the sun with purple-colour'd face", 
      L"Had ta'en his last leave of the weeping morn,"
    } 
  };
   
  
  
  // when possible we should use std::make_shared

  auto sp1 = std::make_shared<Poem>(p1);  // Copy Constructor will be called

  
  std::wcout << "--->Empty Shared pointer ..." << std::endl;
  auto sp2 = std::make_shared<Poem>();    // Default Constructor will be called
  
  std::wcout << "--->Shared pointer for Hugo #1...." << std::endl;
  auto sp3 = std::make_shared<Poem>(
      L"LA CONSCIENCE",
      L"Victor Hugo",       
      Poem::lyrics_t {
        L"Lorsque avec ses enfants vêtus de peaux de bêtes,", 
        L"Échevelé, livide au milieu des tempêtes,",
        L"Caïn se fut enfui de devant Jéhovah,",
        L"....",
        //L"Comme le soir tombait, l’homme sombre arriva",
        //L"Au bas d’une montagne en une grande plaine ;"
      }      
  );

  sp3->set_author(L"'" + sp3->get_author() + L"'");
  std::wcout << "DEBUG/ sp3 Poem: "<< sp3->get_author() << ": " 
             << sp3->get_title() << " verses count = " 
             << sp3->get_lyrics().size() << std::endl;

  for (auto& verse: sp3->get_lyrics()){
    std::wcout << "\t" << verse << std::endl;
  }           

  std::wcout << "--->Shared pointer for Hugo #2...." << std::endl;
   
  std::shared_ptr<Poem> sp4 {
    new Poem(
      L"PUISSANCE ÉGALE BONTÉ",      
      L"Victor Hugo", 
      
      Poem::lyrics_t {
        L"Au commencement, Dieu vit un jour dans l’espace", 
        L"Iblis venir à lui ; Dieu dit : « Veux-tu ta grâce ?",
        L"— Non, dit le Mal. — Alors que me demandes-tu ?",
        L"— Dieu, répondit Iblis de ténèbres vêtu,",
        L"Joutons à qui créera la chose la plus belle."
      }  
    )
  };

  assert(sp4.use_count() == 1);
  auto sp4_copy1 = sp4;
  assert(sp4.use_count() == 2);
  auto sp4_copy2 = sp4;
  assert(sp4.use_count() == 3);
  sp4_copy2.reset();

  
  std::wcout << "--->Shared pointer for an int...." << std::endl;
  std::shared_ptr<int> ptr(new int);
  assert(ptr.use_count() == 1);
  std::shared_ptr<int> ptr_copy = ptr;
  assert(ptr.use_count() == 2);
  *ptr_copy = 10777;
  std::wcout << *ptr << std::endl;
  ptr.reset();
  assert(ptr.use_count() == 0);

  return (EXIT_SUCCESS);
}
