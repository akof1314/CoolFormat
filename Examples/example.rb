#--------------------------------------------------
# Name:           dangdangbook.rb
# Description:    This script is used to download books from http://read.dangdang.com/
#                 The content of book is saved as text file under the same directory with this script
#
#                 Prerequisit:
#                 * gem install hpricot
#
#                 Usage:
#                 ruby dangdangbook.rb book_url
#
#                 eg.
#                 ruby dangdangbook.rb http://read.dangdang.com/book_6011
#
# Author:         Bin Shao <shaobin0604@qq.com> http://aquarium.yo2.cn
# Date:           Oct. 16, 2009
# License:        Apache License, Version 2.0
#--------------------------------------------------

require 'rubygems'
require 'hpricot'
require 'open-uri'
require 'logger'

$log = Logger.new(STDOUT)
$log.level = Logger::INFO

# Build section url
#
# @param book_url String the url for the book
# @param section_id String the id for the section
#
# @return the section url
#
def section_url(book_url, section_id)
  book_url.sub(/book_.+/, section_id)
end

#
# book url must follow the pattern
# http://read.dangdang.com/book_6011
#
def book_url_valid?(book_url)
  /\Ahttp:\/\/read\.dangdang\.com\/book_\d+\Z/i =~ book_url
end

# Download the book with the book_url, the downloaded book file is saved as text file in the same directory  with
# this script
#
# @param book_url String the url for the book
#
# @return true for success, false for fail
#
def download_dangdang_book(book_url)
  unless book_url_valid?(book_url)
    $log.error "book url invalid -- #{book_url}"
    return false
  end

  doc = open(book_url) do |f|
    Hpricot(f)
  end
  
  unless doc.at("/html/body/div/div[@class='sort_cont']/div[@class='catalog_r']/div[@class='catalog']/h2")
    $log.error "book url invalid -- #{book_url}"
    return false
  end

  book_ele = doc.at("/html/body/div/div[@class='sort_cont']/div[@class='book_frame']")
  title = book_ele.at("h2").inner_text
  category = book_ele.at("div[@class='book_prod']/div[@class='prod_cont']/h5").inner_text
  preface = book_ele.at("div[@class='book_prod']/div[@class='prod_cont']/div[@class='prod_detail']/p").inner_text
  author = book_ele.at("div[@class='book_prod']/div[@class='prod_cont']/div[@class='buy_detail']/div[@class='deta_1']/p").inner_text

  chapter_name_list = []
  chapter_section_list = []

  $log.info "find book #{title} successful"
  
  $log.info "title    -> #{title}"
  $log.info "preface  -> #{preface}"
  $log.info "category -> #{category}"
  $log.info "author   -> #{author}"

  doc.search("/html/body/div/div[@class='sort_cont']/div[@class='catalog_r']/div[@class='catalog']/h2").each do |i|
    chapter_name_list << i.inner_text[1..-1]
    ul = i.next_sibling.next_sibling
    section_url_list = []
    ul.search("li/a").each {|a| section_url_list << section_url(book_url, a['href']) }
    chapter_section_list << section_url_list
  end

  $log.debug "chapter_name_list    -> #{chapter_name_list.join(", ")}"
  $log.debug "chapter_section_list -> #{chapter_section_list.inspect}"

  File.open("#{title}.txt", "w") do |f|
    f.puts title
    f.puts
    f.puts category
    f.puts author
    f.puts
    f.puts preface
    f.puts 
    chapter_name_list.each_with_index do |chapter_name, index|
      f.puts "  #{chapter_name}\n\n"
      chapter_section_list[index].each do |section_url|
        section_title, section_content = get_section_content(section_url)
        f.puts section_title
        f.puts section_content
        $log.info "section -- #{section_title} download complete"
      end
    end
  end
  $log.info "book -- #{title} download complete :-)"
  return true
end

# Get the section's title and content
#
# @param section_url String the url for the section
# 
# @return a array consist of two elements, section title and section content
#
def get_section_content(section_url)
  doc = open(section_url) { |f| Hpricot(f) }
  title = doc.at("/html/body/div.cont_page/div.cont_detail/h2").inner_text
  content = doc.at("#content").inner_html

  content.gsub!("<br />", "").gsub!("\t", " ")

  $log.debug "title -> #{title}"
  $log.debug "content -> #{content}"
  [title, content]
end

if __FILE__ == $0
  if ARGV.length != 1
    puts "Usage: ruby dangdangbook.rb book_url"
  else
    download_dangdang_book(ARGV[0])
  end
end