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

class Poem{
  public:
    using lyrics_t = std::vector<std::string>;

  private:
    std::string title_ = u8"";
    std::string author_ = u8"";
    lyrics_t lyrics_ = {};

  public:
    Poem(){
      std::cout << "Calling *Default* Constructor" <<  std::hex 
                 << ", this = " << this << std::endl;
    }

    Poem(const std::string& title, const std::string& author, 
         const lyrics_t& lyrics): 
        title_{title}, author_{author}, lyrics_{lyrics}{
      std::cout << "Calling Constructor for: " << title <<", " << author
                 <<  std::hex << ", this = " << this << std::endl;

    } 
     
    Poem(const Poem& other): title_{other.title_}, author_{other.author_}, \
                              lyrics_{other.lyrics_} {
      std::cout << "Calling *Copy* Constructor" <<  std::hex 
                 << ", this = " << this << std::endl;

    } 

    Poem(const Poem&& other) noexcept:  
      title_{std::move(other.title_)}, 
      author_{std::move(other.author_)}, 
      lyrics_{std::move(other.lyrics_)}  {
      std::cout << "Calling *Move* Constructor" <<  std::hex 
                 << ", this = " << this << std::endl;
     
    } 


    Poem& operator=(const Poem& other){
      std::cout << "Calling assignment operator" << std::hex 
                 << ", this = " << this << std::endl;
      title_ = other.title_;
      author_ = other.author_;
      lyrics_ = other.lyrics_;
      return (*this);
    } 

    Poem& operator=(Poem&& other){
      std::cout << "Calling *move* assignment operator" <<  std::hex 
                 << ", this = " << this << std::endl;
      title_ = std::move(other.title_);
      author_ = std::move(other.author_);
      lyrics_ = std::move(other.lyrics_);
      return (*this);
    } 

    ~Poem() noexcept {
      std::cout << "Calling Destructor for: " << title_ << ", " << author_ 
                 << std::hex << ", this = " << this << std::endl;
    } 
    
    const std::string& get_title(void) const{
      return this->title_;
    }

    const std::string& get_author(void) const{
      return this->author_;
    }  

    const lyrics_t& get_lyrics(void) const {
      return this->lyrics_;
    }

    void set_author(const std::string& author){
      this->author_= author;
    }

};

static
void pass_by_value_func(std::shared_ptr<Poem> sp){
  std::cout << __func__ << ": " << sp->get_author() << ": " 
            << sp->get_title() << " verses count = " 
            << sp->get_lyrics().size() 
            << " use count = " << sp.use_count() << std::endl;

}

static
void pass_by_ref_func(std::shared_ptr<Poem>& sp){
  std::cout << __func__ << ": " << sp->get_author() << ": " 
            << sp->get_title() << " verses count = " 
            << sp->get_lyrics().size() 
            << " use count = " << sp.use_count() << std::endl;

}

int main(){

  Poem p1 {
    u8"Venus and Adonis",
    u8"William Shakespeare",    
    {
      u8"EVEN as the sun with purple-colour'd face", 
      u8"Had ta'en his last leave of the weeping morn,"
    } 
  };
   
  
  
  // when possible we should use std::make_shared

  auto sp1 = std::make_shared<Poem>(p1);  // Copy Constructor will be called

  
  std::cout << "--->Empty Shared pointer ..." << std::endl;
  auto sp2 = std::make_shared<Poem>();    // Default Constructor will be called
  
  std::cout << "--->Shared pointer for Hugo #1...." << std::endl;
  auto sp3 = std::make_shared<Poem>(
      u8"LA CONSCIENCE",
      u8"Victor Hugo",       
      Poem::lyrics_t {
        u8"Lorsque avec ses enfants vêtus de peaux de bêtes,", 
        u8"Échevelé, livide au milieu des tempêtes,",
        u8"Caïn se fut enfui de devant Jéhovah,",
        u8"Comme le soir tombait, l’homme sombre arriva",
        u8"Au bas d’une montagne en une grande plaine ;"
      }      
  );

  sp3->set_author(u8"'" + sp3->get_author() + u8"'");
  std::cout << "DEBUG/ sp3 Poem: "<< sp3->get_author() << ": " 
             << sp3->get_title() << " verses count = " 
             << sp3->get_lyrics().size() << std::endl;

  for (auto& verse: sp3->get_lyrics()){
    std::cout << "\t" << verse << std::endl;
  }           
  
  std::cout << "[Before passing by value] use_count = " << sp3.use_count() << std::endl;
  pass_by_value_func(sp3);
  std::cout << "[After passing by value] use_count = " << sp3.use_count() << std::endl;


  std::cout << "[Before passing by reference] use_count = " << sp3.use_count() << std::endl;
  pass_by_ref_func(sp3);
  std::cout << "[After passing by reference] use_count = " << sp3.use_count() << std::endl;


  std::cout << "--->Shared pointer for Hugo #2...." << std::endl;
   
  std::shared_ptr<Poem> sp4 {
    new Poem(
      u8"PUISSANCE ÉGALE BONTÉ",      
      u8"Victor Hugo", 
      
      Poem::lyrics_t {
        u8"Au commencement, Dieu vit un jour dans l’espace", 
        u8"Iblis venir à lui ; Dieu dit : « Veux-tu ta grâce ?",
        u8"— Non, dit le Mal. — Alors que me demandes-tu ?",
        u8"— Dieu, répondit Iblis de ténèbres vêtu,",
        u8"Joutons à qui créera la chose la plus belle."
      }  
    )
  };

  assert(sp4.use_count() == 1);



  auto sp4_copy1 = sp4;
  assert(sp4.use_count() == 2);
  auto sp4_copy2 = sp4;
  assert(sp4.use_count() == 3);
  sp4_copy2.reset();

  

  std::cout << "--->Shared pointer for an int...." << std::endl;
  std::shared_ptr<int> ptr(new int);
  assert(ptr.use_count() == 1);
  std::shared_ptr<int> ptr_copy = ptr;
  assert(ptr.use_count() == 2);
  *ptr_copy = 10777;
  std::cout << *ptr << std::endl;
  ptr.reset();
  assert(ptr.use_count() == 0);

  return (EXIT_SUCCESS);
}
