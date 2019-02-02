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

class Poem{
  public:
    using lyrics_t = std::vector<std::wstring>;

  private:
    std::wstring title_ = L"";
    std::wstring author_ = L"";
    lyrics_t lyrics_ = {};

  public:
    Poem(){
      std::wcout << "Calling *Default* Constuctor" <<  std::hex 
                 << ", this = " << this << std::endl;
    }

    Poem(const std::wstring& title, const std::wstring& author, 
         const lyrics_t& lyrics): 
        title_{title}, author_{author}, lyrics_{lyrics}{
      std::wcout << "Calling Constuctor for: " << title <<", " << author
                 <<  std::hex << ", this = " << this << std::endl;

    } 
     
    Poem(const Poem& other): title_{other.title_}, author_{other.author_}, \
                              lyrics_{other.lyrics_} {
      std::wcout << "Calling *Copy* Constuctor" <<  std::hex 
                 << ", this = " << this << std::endl;

    } 

    Poem(const Poem&& other) noexcept:  
      title_{std::move(other.title_)}, 
      author_{std::move(other.author_)}, 
      lyrics_{std::move(other.lyrics_)}  {
      std::wcout << "Calling *Move* Constuctor" <<  std::hex 
                 << ", this = " << this << std::endl;
     
    } 


    Poem& operator=(const Poem& other){
      std::wcout << "Calling asignment operator" << std::hex 
                 << ", this = " << this << std::endl;
      title_ = other.title_;
      author_ = other.author_;
      lyrics_ = other.lyrics_;
      return (*this);
    } 

    Poem& operator=(Poem&& other){
      std::wcout << "Calling *move* asignment operator" <<  std::hex 
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
    
};

int main(){

  Poem p1 {
    L"William Shakespeare", 
    L"Venus and Adonis",
    {
      L"EVEN as the sun with purple-colour'd face", 
      L"Had ta'en his last leave of the weeping morn,"
    } 
  };
   
  
  
  // when possible we should use std::make_shared

  auto sp1 = std::make_shared<Poem>(p1);  // Copy Constructor will be called


  auto sp2 = std::make_shared<Poem>();    // Default Constructor will be called
  
  auto sp3 = std::make_shared<Poem>(
      L"William Shakespeare", 
      L"Venus and Adonis",
      Poem::lyrics_t {
        L"EVEN as the sun with purple-colour'd face", 
        L"Had ta'en his last leave of the weeping morn,",
        L"...."
      }      
  );

  Poem* poem4 = new Poem(
      L"William Shakespeare", 
      L"Venus and Adonis",
      Poem::lyrics_t {
        L"EVEN as the sun with purple-colour'd face", 
        L"Had ta'en his last leave of the weeping morn,",
        L"...."
      }
   );

  
  auto sp4 = std::make_shared<Poem>( *poem4 );
  
  std::wcout << sp4.use_count() << std::endl;
  
  
  
  //sp3 = sp2;


  return (EXIT_SUCCESS);
}
