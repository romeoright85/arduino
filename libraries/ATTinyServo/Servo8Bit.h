  


<!DOCTYPE html>
<html>
  <head prefix="og: http://ogp.me/ns# fb: http://ogp.me/ns/fb# githubog: http://ogp.me/ns/fb/githubog#">
    <meta charset='utf-8'>
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
        <title>Servo8Bit/Servo8Bit.h at master · fri000/Servo8Bit · GitHub</title>
    <link rel="search" type="application/opensearchdescription+xml" href="/opensearch.xml" title="GitHub" />
    <link rel="fluid-icon" href="https://github.com/fluidicon.png" title="GitHub" />
    <link rel="apple-touch-icon" sizes="57x57" href="/apple-touch-icon-114.png" />
    <link rel="apple-touch-icon" sizes="114x114" href="/apple-touch-icon-114.png" />
    <link rel="apple-touch-icon" sizes="72x72" href="/apple-touch-icon-144.png" />
    <link rel="apple-touch-icon" sizes="144x144" href="/apple-touch-icon-144.png" />
    <link rel="logo" type="image/svg" href="http://github-media-downloads.s3.amazonaws.com/github-logo.svg" />
    <link rel="xhr-socket" href="/_sockets">
    <meta name="msapplication-TileImage" content="/windows-tile.png">
    <meta name="msapplication-TileColor" content="#ffffff">

    
    
    <link rel="icon" type="image/x-icon" href="/favicon.ico" />

    <meta content="authenticity_token" name="csrf-param" />
<meta content="CxMFveaFLNZRhpktmT2TNzfKGg0H9r6tu0aHyuGUnWc=" name="csrf-token" />

    <link href="https://a248.e.akamai.net/assets.github.com/assets/github-8424f74a551e0aa008a2555ebdb672c36b471576.css" media="all" rel="stylesheet" type="text/css" />
    <link href="https://a248.e.akamai.net/assets.github.com/assets/github2-4ee688f9a05c8f1a8143eb8b0de6aaf41e591dce.css" media="all" rel="stylesheet" type="text/css" />
    


      <script src="https://a248.e.akamai.net/assets.github.com/assets/frameworks-bafee0a321be765ed924edd4c746d8af68510845.js" type="text/javascript"></script>
      <script src="https://a248.e.akamai.net/assets.github.com/assets/github-2c28e209e1384e8714f27a9b337d9b2b641cc016.js" type="text/javascript"></script>
      
      <meta http-equiv="x-pjax-version" content="18ddb64371a9717b78781cf2412ea4d0">

        <link data-pjax-transient rel='permalink' href='/fri000/Servo8Bit/blob/d5a801c50fe70cb141aa2cbe48f1f12438b61b40/Servo8Bit.h'>
    <meta property="og:title" content="Servo8Bit"/>
    <meta property="og:type" content="githubog:gitrepository"/>
    <meta property="og:url" content="https://github.com/fri000/Servo8Bit"/>
    <meta property="og:image" content="https://secure.gravatar.com/avatar/741bf313a44ebd402ea8ea58e039f111?s=420&amp;d=https://a248.e.akamai.net/assets.github.com%2Fimages%2Fgravatars%2Fgravatar-user-420.png"/>
    <meta property="og:site_name" content="GitHub"/>
    <meta property="og:description" content="Servo8Bit - Servo library for the ATtiny45 and the ATtiny85"/>
    <meta property="twitter:card" content="summary"/>
    <meta property="twitter:site" content="@GitHub">
    <meta property="twitter:title" content="fri000/Servo8Bit"/>

    <meta name="description" content="Servo8Bit - Servo library for the ATtiny45 and the ATtiny85" />

  <link href="https://github.com/fri000/Servo8Bit/commits/master.atom" rel="alternate" title="Recent Commits to Servo8Bit:master" type="application/atom+xml" />

  </head>


  <body class="logged_out page-blob windows vis-public env-production  ">
    <div id="wrapper">

      

      
      
      

      
      <div class="header header-logged-out">
  <div class="container clearfix">

      <a class="header-logo-wordmark" href="https://github.com/">Github</a>

      <ul class="top-nav">
          <li class="explore"><a href="https://github.com/explore">Explore GitHub</a></li>
        <li class="search"><a href="https://github.com/search">Search</a></li>
        <li class="features"><a href="https://github.com/features">Features</a></li>
          <li class="blog"><a href="https://github.com/blog">Blog</a></li>
      </ul>

    <div class="header-actions">
        <a class="button primary" href="https://github.com/signup">Sign up for free</a>
      <a class="button" href="https://github.com/login?return_to=%2Ffri000%2FServo8Bit%2Fblob%2Fmaster%2FServo8Bit.h">Sign in</a>
    </div>

  </div>
</div>


      

      


            <div class="site hfeed" itemscope itemtype="http://schema.org/WebPage">
      <div class="hentry">
        
        <div class="pagehead repohead instapaper_ignore readability-menu ">
          <div class="container">
            <div class="title-actions-bar">
              


<ul class="pagehead-actions">



    <li>
      <a href="/login?return_to=%2Ffri000%2FServo8Bit"
        class="minibutton js-toggler-target star-button entice tooltipped upwards"
        title="You must be signed in to use this feature" rel="nofollow">
        <span class="mini-icon mini-icon-star"></span>Star
      </a>
      <a class="social-count js-social-count" href="/fri000/Servo8Bit/stargazers">
        10
      </a>
    </li>
    <li>
      <a href="/login?return_to=%2Ffri000%2FServo8Bit"
        class="minibutton js-toggler-target fork-button entice tooltipped upwards"
        title="You must be signed in to fork a repository" rel="nofollow">
        <span class="mini-icon mini-icon-fork"></span>Fork
      </a>
      <a href="/fri000/Servo8Bit/network" class="social-count">
        3
      </a>
    </li>
</ul>

              <h1 itemscope itemtype="http://data-vocabulary.org/Breadcrumb" class="entry-title public">
                <span class="repo-label"><span>public</span></span>
                <span class="mega-icon mega-icon-public-repo"></span>
                <span class="author vcard">
                  <a href="/fri000" class="url fn" itemprop="url" rel="author">
                  <span itemprop="title">fri000</span>
                  </a></span> /
                <strong><a href="/fri000/Servo8Bit" class="js-current-repository">Servo8Bit</a></strong>
              </h1>
            </div>

            
  <ul class="tabs">
    <li><a href="/fri000/Servo8Bit" class="selected" highlight="repo_source repo_downloads repo_commits repo_tags repo_branches">Code</a></li>
    <li><a href="/fri000/Servo8Bit/network" highlight="repo_network">Network</a></li>
    <li><a href="/fri000/Servo8Bit/pulls" highlight="repo_pulls">Pull Requests <span class='counter'>0</span></a></li>

      <li><a href="/fri000/Servo8Bit/issues" highlight="repo_issues">Issues <span class='counter'>0</span></a></li>



    <li><a href="/fri000/Servo8Bit/graphs" highlight="repo_graphs repo_contributors">Graphs</a></li>


  </ul>
  
<div class="tabnav">

  <span class="tabnav-right">
    <ul class="tabnav-tabs">
          <li><a href="/fri000/Servo8Bit/tags" class="tabnav-tab" highlight="repo_tags">Tags <span class="counter ">1</span></a></li>
    </ul>
    
  </span>

  <div class="tabnav-widget scope">


    <div class="select-menu js-menu-container js-select-menu js-branch-menu">
      <a class="minibutton select-menu-button js-menu-target" data-hotkey="w" data-ref="master">
        <span class="mini-icon mini-icon-branch"></span>
        <i>branch:</i>
        <span class="js-select-button">master</span>
      </a>

      <div class="select-menu-modal-holder js-menu-content js-navigation-container">

        <div class="select-menu-modal">
          <div class="select-menu-header">
            <span class="select-menu-title">Switch branches/tags</span>
            <span class="mini-icon mini-icon-remove-close js-menu-close"></span>
          </div> <!-- /.select-menu-header -->

          <div class="select-menu-filters">
            <div class="select-menu-text-filter">
              <input type="text" id="commitish-filter-field" class="js-filterable-field js-navigation-enable" placeholder="Filter branches/tags">
            </div>
            <div class="select-menu-tabs">
              <ul>
                <li class="select-menu-tab">
                  <a href="#" data-tab-filter="branches" class="js-select-menu-tab">Branches</a>
                </li>
                <li class="select-menu-tab">
                  <a href="#" data-tab-filter="tags" class="js-select-menu-tab">Tags</a>
                </li>
              </ul>
            </div><!-- /.select-menu-tabs -->
          </div><!-- /.select-menu-filters -->

          <div class="select-menu-list select-menu-tab-bucket js-select-menu-tab-bucket css-truncate" data-tab-filter="branches">

            <div data-filterable-for="commitish-filter-field" data-filterable-type="substring">

                <div class="select-menu-item js-navigation-item js-navigation-target selected">
                  <span class="select-menu-item-icon mini-icon mini-icon-confirm"></span>
                  <a href="/fri000/Servo8Bit/blob/master/Servo8Bit.h" class="js-navigation-open select-menu-item-text js-select-button-text css-truncate-target" data-name="master" rel="nofollow" title="master">master</a>
                </div> <!-- /.select-menu-item -->
            </div>

              <div class="select-menu-no-results">Nothing to show</div>
          </div> <!-- /.select-menu-list -->


          <div class="select-menu-list select-menu-tab-bucket js-select-menu-tab-bucket css-truncate" data-tab-filter="tags">
            <div data-filterable-for="commitish-filter-field" data-filterable-type="substring">

                <div class="select-menu-item js-navigation-item js-navigation-target ">
                  <span class="select-menu-item-icon mini-icon mini-icon-confirm"></span>
                  <a href="/fri000/Servo8Bit/blob/V0.5/Servo8Bit.h" class="js-navigation-open select-menu-item-text js-select-button-text css-truncate-target" data-name="V0.5" rel="nofollow" title="V0.5">V0.5</a>
                </div> <!-- /.select-menu-item -->
            </div>

            <div class="select-menu-no-results">Nothing to show</div>

          </div> <!-- /.select-menu-list -->

        </div> <!-- /.select-menu-modal -->
      </div> <!-- /.select-menu-modal-holder -->
    </div> <!-- /.select-menu -->

  </div> <!-- /.scope -->

  <ul class="tabnav-tabs">
    <li><a href="/fri000/Servo8Bit" class="selected tabnav-tab" highlight="repo_source">Files</a></li>
    <li><a href="/fri000/Servo8Bit/commits/master" class="tabnav-tab" highlight="repo_commits">Commits</a></li>
    <li><a href="/fri000/Servo8Bit/branches" class="tabnav-tab" highlight="repo_branches" rel="nofollow">Branches <span class="counter ">1</span></a></li>
  </ul>

</div>

  
  
  


            
          </div>
        </div><!-- /.repohead -->

        <div id="js-repo-pjax-container" class="container context-loader-container" data-pjax-container>
          


<!-- blob contrib key: blob_contributors:v21:45467fe4f6a03cef8d28a21db0f67fd4 -->
<!-- blob contrib frag key: views10/v8/blob_contributors:v21:45467fe4f6a03cef8d28a21db0f67fd4 -->


<div id="slider">
    <div class="frame-meta">

      <p title="This is a placeholder element" class="js-history-link-replace hidden"></p>

        <div class="breadcrumb">
          <span class='bold'><span itemscope="" itemtype="http://data-vocabulary.org/Breadcrumb"><a href="/fri000/Servo8Bit" class="js-slide-to" data-branch="master" data-direction="back" itemscope="url"><span itemprop="title">Servo8Bit</span></a></span></span><span class="separator"> / </span><strong class="final-path">Servo8Bit.h</strong> <span class="js-zeroclipboard zeroclipboard-button" data-clipboard-text="Servo8Bit.h" data-copied-hint="copied!" title="copy to clipboard"><span class="mini-icon mini-icon-clipboard"></span></span>
        </div>

      <a href="/fri000/Servo8Bit/find/master" class="js-slide-to" data-hotkey="t" style="display:none">Show File Finder</a>


        
  <div class="commit file-history-tease">
    <img class="main-avatar" height="24" src="https://secure.gravatar.com/avatar/741bf313a44ebd402ea8ea58e039f111?s=140&amp;d=https://a248.e.akamai.net/assets.github.com%2Fimages%2Fgravatars%2Fgravatar-user-420.png" width="24" />
    <span class="author"><a href="/fri000" rel="author">fri000</a></span>
    <time class="js-relative-date" datetime="2011-11-22T19:53:19-08:00" title="2011-11-22 19:53:19">November 22, 2011</time>
    <div class="commit-title">
        <a href="/fri000/Servo8Bit/commit/a889801b69144c260fe33d8f26f7641aee415f6f" class="message">Moved the timer init code to happen when the first servo is attached,…</a>
    </div>

    <div class="participation">
      <p class="quickstat"><a href="#blob_contributors_box" rel="facebox"><strong>2</strong> contributors</a></p>
          <a class="avatar tooltipped downwards" title="fri000" href="/fri000/Servo8Bit/commits/master/Servo8Bit.h?author=fri000"><img height="20" src="https://secure.gravatar.com/avatar/741bf313a44ebd402ea8ea58e039f111?s=140&amp;d=https://a248.e.akamai.net/assets.github.com%2Fimages%2Fgravatars%2Fgravatar-user-420.png" width="20" /></a>
    <a class="avatar tooltipped downwards" title="justjoheinz" href="/fri000/Servo8Bit/commits/master/Servo8Bit.h?author=justjoheinz"><img height="20" src="https://secure.gravatar.com/avatar/02862e49d4152f580a2c81b66d00ea2f?s=140&amp;d=https://a248.e.akamai.net/assets.github.com%2Fimages%2Fgravatars%2Fgravatar-user-420.png" width="20" /></a>


    </div>
    <div id="blob_contributors_box" style="display:none">
      <h2>Users on GitHub who have contributed to this file</h2>
      <ul class="facebox-user-list">
        <li>
          <img height="24" src="https://secure.gravatar.com/avatar/741bf313a44ebd402ea8ea58e039f111?s=140&amp;d=https://a248.e.akamai.net/assets.github.com%2Fimages%2Fgravatars%2Fgravatar-user-420.png" width="24" />
          <a href="/fri000">fri000</a>
        </li>
        <li>
          <img height="24" src="https://secure.gravatar.com/avatar/02862e49d4152f580a2c81b66d00ea2f?s=140&amp;d=https://a248.e.akamai.net/assets.github.com%2Fimages%2Fgravatars%2Fgravatar-user-420.png" width="24" />
          <a href="/justjoheinz">justjoheinz</a>
        </li>
      </ul>
    </div>
  </div>


    </div><!-- ./.frame-meta -->

    <div class="frames">
      <div class="frame" data-permalink-url="/fri000/Servo8Bit/blob/d5a801c50fe70cb141aa2cbe48f1f12438b61b40/Servo8Bit.h" data-title="Servo8Bit/Servo8Bit.h at master · fri000/Servo8Bit · GitHub" data-type="blob">

        <div id="files" class="bubble">
          <div class="file">
            <div class="meta">
              <div class="info">
                <span class="icon"><b class="mini-icon mini-icon-text-file"></b></span>
                <span class="mode" title="File Mode">file</span>
                  <span>87 lines (64 sloc)</span>
                <span>3.809 kb</span>
              </div>
              <div class="actions">
                <div class="button-group">
                      <a class="minibutton js-entice" href=""
                         data-entice="You must be signed in and on a branch to make or propose changes">Edit</a>
                  <a href="/fri000/Servo8Bit/raw/master/Servo8Bit.h" class="button minibutton " id="raw-url">Raw</a>
                    <a href="/fri000/Servo8Bit/blame/master/Servo8Bit.h" class="button minibutton ">Blame</a>
                  <a href="/fri000/Servo8Bit/commits/master/Servo8Bit.h" class="button minibutton " rel="nofollow">History</a>
                </div><!-- /.button-group -->
              </div><!-- /.actions -->

            </div>
                <div class="data type-objective-c js-blob-data">
      <table cellpadding="0" cellspacing="0" class="lines">
        <tr>
          <td>
            <pre class="line_numbers"><span id="L1" rel="#L1">1</span>
<span id="L2" rel="#L2">2</span>
<span id="L3" rel="#L3">3</span>
<span id="L4" rel="#L4">4</span>
<span id="L5" rel="#L5">5</span>
<span id="L6" rel="#L6">6</span>
<span id="L7" rel="#L7">7</span>
<span id="L8" rel="#L8">8</span>
<span id="L9" rel="#L9">9</span>
<span id="L10" rel="#L10">10</span>
<span id="L11" rel="#L11">11</span>
<span id="L12" rel="#L12">12</span>
<span id="L13" rel="#L13">13</span>
<span id="L14" rel="#L14">14</span>
<span id="L15" rel="#L15">15</span>
<span id="L16" rel="#L16">16</span>
<span id="L17" rel="#L17">17</span>
<span id="L18" rel="#L18">18</span>
<span id="L19" rel="#L19">19</span>
<span id="L20" rel="#L20">20</span>
<span id="L21" rel="#L21">21</span>
<span id="L22" rel="#L22">22</span>
<span id="L23" rel="#L23">23</span>
<span id="L24" rel="#L24">24</span>
<span id="L25" rel="#L25">25</span>
<span id="L26" rel="#L26">26</span>
<span id="L27" rel="#L27">27</span>
<span id="L28" rel="#L28">28</span>
<span id="L29" rel="#L29">29</span>
<span id="L30" rel="#L30">30</span>
<span id="L31" rel="#L31">31</span>
<span id="L32" rel="#L32">32</span>
<span id="L33" rel="#L33">33</span>
<span id="L34" rel="#L34">34</span>
<span id="L35" rel="#L35">35</span>
<span id="L36" rel="#L36">36</span>
<span id="L37" rel="#L37">37</span>
<span id="L38" rel="#L38">38</span>
<span id="L39" rel="#L39">39</span>
<span id="L40" rel="#L40">40</span>
<span id="L41" rel="#L41">41</span>
<span id="L42" rel="#L42">42</span>
<span id="L43" rel="#L43">43</span>
<span id="L44" rel="#L44">44</span>
<span id="L45" rel="#L45">45</span>
<span id="L46" rel="#L46">46</span>
<span id="L47" rel="#L47">47</span>
<span id="L48" rel="#L48">48</span>
<span id="L49" rel="#L49">49</span>
<span id="L50" rel="#L50">50</span>
<span id="L51" rel="#L51">51</span>
<span id="L52" rel="#L52">52</span>
<span id="L53" rel="#L53">53</span>
<span id="L54" rel="#L54">54</span>
<span id="L55" rel="#L55">55</span>
<span id="L56" rel="#L56">56</span>
<span id="L57" rel="#L57">57</span>
<span id="L58" rel="#L58">58</span>
<span id="L59" rel="#L59">59</span>
<span id="L60" rel="#L60">60</span>
<span id="L61" rel="#L61">61</span>
<span id="L62" rel="#L62">62</span>
<span id="L63" rel="#L63">63</span>
<span id="L64" rel="#L64">64</span>
<span id="L65" rel="#L65">65</span>
<span id="L66" rel="#L66">66</span>
<span id="L67" rel="#L67">67</span>
<span id="L68" rel="#L68">68</span>
<span id="L69" rel="#L69">69</span>
<span id="L70" rel="#L70">70</span>
<span id="L71" rel="#L71">71</span>
<span id="L72" rel="#L72">72</span>
<span id="L73" rel="#L73">73</span>
<span id="L74" rel="#L74">74</span>
<span id="L75" rel="#L75">75</span>
<span id="L76" rel="#L76">76</span>
<span id="L77" rel="#L77">77</span>
<span id="L78" rel="#L78">78</span>
<span id="L79" rel="#L79">79</span>
<span id="L80" rel="#L80">80</span>
<span id="L81" rel="#L81">81</span>
<span id="L82" rel="#L82">82</span>
<span id="L83" rel="#L83">83</span>
<span id="L84" rel="#L84">84</span>
<span id="L85" rel="#L85">85</span>
<span id="L86" rel="#L86">86</span>
</pre>
          </td>
          <td width="100%">
                  <div class="highlight"><pre><div class='line' id='LC1'><span class="cm">/*</span></div><div class='line' id='LC2'><span class="cm"> Servo8Bit.cpp - Interrupt driven Servo library for the Attiny45 and Attiny85 that uses an 8 bit timer.</span></div><div class='line' id='LC3'><span class="cm"> Version 0.6</span></div><div class='line' id='LC4'><span class="cm"> Copyright (c) 2011 Ilya Brutman.  All right reserved.</span></div><div class='line' id='LC5'><br/></div><div class='line' id='LC6'><span class="cm"> This library is free software; you can redistribute it and/or</span></div><div class='line' id='LC7'><span class="cm"> modify it under the terms of the GNU Lesser General Public</span></div><div class='line' id='LC8'><span class="cm"> License as published by the Free Software Foundation; either</span></div><div class='line' id='LC9'><span class="cm"> version 2.1 of the License, or (at your option) any later version.</span></div><div class='line' id='LC10'><br/></div><div class='line' id='LC11'><span class="cm"> This library is distributed in the hope that it will be useful,</span></div><div class='line' id='LC12'><span class="cm"> but WITHOUT ANY WARRANTY; without even the implied warranty of</span></div><div class='line' id='LC13'><span class="cm"> MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU</span></div><div class='line' id='LC14'><span class="cm"> Lesser General Public License for more details.</span></div><div class='line' id='LC15'><br/></div><div class='line' id='LC16'><span class="cm"> You should have received a copy of the GNU Lesser General Public</span></div><div class='line' id='LC17'><span class="cm"> License along with this library; if not, write to the Free Software</span></div><div class='line' id='LC18'><span class="cm"> Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA</span></div><div class='line' id='LC19'><span class="cm"> */</span></div><div class='line' id='LC20'><br/></div><div class='line' id='LC21'><br/></div><div class='line' id='LC22'><span class="cm">/*</span></div><div class='line' id='LC23'><br/></div><div class='line' id='LC24'><span class="cm">  A servo is activated by creating an instance of the Servo8Bit class passing the desired pin to the attach() method.</span></div><div class='line' id='LC25'><span class="cm">  The servos are pulsed in the background using the value most recently written using the write() method</span></div><div class='line' id='LC26'><br/></div><div class='line' id='LC27'><br/></div><div class='line' id='LC28'><span class="cm">  The methods are:</span></div><div class='line' id='LC29'><br/></div><div class='line' id='LC30'><span class="cm">   Servo8Bit - Class for manipulating servo motors connected to Attiny pins.</span></div><div class='line' id='LC31'><br/></div><div class='line' id='LC32'><span class="cm">   attach(pin)           - Attaches a servo motor to an i/o pin.</span></div><div class='line' id='LC33'><span class="cm">   attach(pin, min, max) - Attaches to a pin setting min and max values in microseconds</span></div><div class='line' id='LC34'><span class="cm">                           default min is 544, max is 2400</span></div><div class='line' id='LC35'><br/></div><div class='line' id='LC36'><span class="cm">   write()               - Sets the servo angle in degrees.  (invalid angle that is valid as pulse in microseconds is treated as microseconds)</span></div><div class='line' id='LC37'><span class="cm">   writeMicroseconds()   - Sets the servo pulse width in microseconds</span></div><div class='line' id='LC38'><span class="cm">   read()                - Gets the last written servo pulse width as an angle between 0 and 180.</span></div><div class='line' id='LC39'><span class="cm">   readMicroseconds()    - Gets the last written servo pulse width in microseconds.</span></div><div class='line' id='LC40'><span class="cm">   attached()            - Returns true if there is a servo attached.</span></div><div class='line' id='LC41'><span class="cm">   detach()              - Stops an attached servos from pulsing its i/o pin.</span></div><div class='line' id='LC42'><span class="cm"> */</span></div><div class='line' id='LC43'><br/></div><div class='line' id='LC44'><span class="cp">#ifndef Servo8Bit_h</span></div><div class='line' id='LC45'><span class="cp">#define Servo8Bit_h</span></div><div class='line' id='LC46'><br/></div><div class='line' id='LC47'><span class="cp">#include &lt;inttypes.h&gt;</span></div><div class='line' id='LC48'><br/></div><div class='line' id='LC49'><br/></div><div class='line' id='LC50'><span class="c1">//Options</span></div><div class='line' id='LC51'><span class="c1">//pick one, comment out the other one out:</span></div><div class='line' id='LC52'><span class="c1">//#define USE_TIMER0</span></div><div class='line' id='LC53'><span class="cp">#define USE_TIMER1</span></div><div class='line' id='LC54'><br/></div><div class='line' id='LC55'><br/></div><div class='line' id='LC56'><span class="n">class</span> <span class="n">Servo8Bit</span></div><div class='line' id='LC57'><span class="p">{</span></div><div class='line' id='LC58'><span class="nl">public:</span></div><div class='line' id='LC59'>&nbsp;&nbsp;<span class="n">Servo8Bit</span><span class="p">();</span></div><div class='line' id='LC60'>&nbsp;&nbsp;<span class="c1">//TODO: create destructor</span></div><div class='line' id='LC61'>&nbsp;&nbsp;<span class="kt">uint8_t</span> <span class="nf">attach</span><span class="p">(</span><span class="kt">uint8_t</span> <span class="n">pin</span><span class="p">);</span>              <span class="c1">// attach the given pin to the next free channel, returns channel number or 0 if failure</span></div><div class='line' id='LC62'>&nbsp;&nbsp;<span class="kt">uint8_t</span> <span class="nf">attach</span><span class="p">(</span><span class="kt">uint8_t</span> <span class="n">pin</span><span class="p">,</span> <span class="kt">uint16_t</span> <span class="n">newMin</span><span class="p">,</span> <span class="kt">uint16_t</span> <span class="n">newMax</span><span class="p">);</span> <span class="c1">// as above but also sets min and max values for writes.</span></div><div class='line' id='LC63'>&nbsp;&nbsp;<span class="kt">void</span> <span class="nf">detach</span><span class="p">();</span></div><div class='line' id='LC64'><br/></div><div class='line' id='LC65'>&nbsp;&nbsp;<span class="kt">void</span> <span class="nf">write</span><span class="p">(</span><span class="kt">uint16_t</span> <span class="n">value</span><span class="p">);</span>               <span class="c1">// if value is &lt; 200 its treated as an angle, otherwise as pulse width in microseconds</span></div><div class='line' id='LC66'>&nbsp;&nbsp;<span class="kt">void</span> <span class="nf">writeMicroseconds</span><span class="p">(</span><span class="kt">uint16_t</span> <span class="n">value</span><span class="p">);</span>   <span class="c1">// Write pulse width in microseconds</span></div><div class='line' id='LC67'>&nbsp;&nbsp;<span class="kt">uint16_t</span> <span class="nf">read</span><span class="p">();</span>                          <span class="c1">// returns current pulse width as an angle between 0 and 180 degrees</span></div><div class='line' id='LC68'>&nbsp;&nbsp;<span class="kt">uint16_t</span> <span class="nf">readMicroseconds</span><span class="p">();</span>              <span class="c1">// returns current pulse width in microseconds for this servo</span></div><div class='line' id='LC69'>&nbsp;&nbsp;<span class="kt">bool</span> <span class="nf">attached</span><span class="p">();</span>                          <span class="c1">// return true if this servo is attached, otherwise false</span></div><div class='line' id='LC70'><br/></div><div class='line' id='LC71'><span class="nl">private:</span></div><div class='line' id='LC72'>&nbsp;&nbsp;&nbsp;<span class="c1">//private constants</span></div><div class='line' id='LC73'>&nbsp;&nbsp;&nbsp;<span class="k">static</span> <span class="k">const</span> <span class="kt">uint16_t</span> <span class="n">kDefaultMinimalPulse</span> <span class="o">=</span> <span class="mi">544</span><span class="p">;</span></div><div class='line' id='LC74'>&nbsp;&nbsp;&nbsp;<span class="k">static</span> <span class="k">const</span> <span class="kt">uint16_t</span> <span class="n">kDefaultMaximumPulse</span> <span class="o">=</span> <span class="mi">2400</span><span class="p">;</span></div><div class='line' id='LC75'><br/></div><div class='line' id='LC76'>&nbsp;&nbsp;&nbsp;<span class="c1">//private variables</span></div><div class='line' id='LC77'>&nbsp;&nbsp;&nbsp;<span class="kt">uint8_t</span>  <span class="n">myServoNumber</span><span class="p">;</span>                  <span class="c1">// Our ID number that we get from the ServoSequencer after we register with it</span></div><div class='line' id='LC78'>&nbsp;&nbsp;&nbsp;<span class="kt">uint8_t</span>  <span class="n">invalidServoNumber</span><span class="p">;</span>             <span class="c1">// value that represents and invalid servo number. This is set only once.</span></div><div class='line' id='LC79'>&nbsp;&nbsp;&nbsp;<span class="kt">uint16_t</span> <span class="n">myMin</span><span class="p">;</span>                          <span class="c1">// minimum pulse length that corresponds to the angle of 0 degrees</span></div><div class='line' id='LC80'>&nbsp;&nbsp;&nbsp;<span class="kt">uint16_t</span> <span class="n">myMax</span><span class="p">;</span>                          <span class="c1">// maximum pulse length that corresponds to the angle of 180 degrees</span></div><div class='line' id='LC81'><br/></div><div class='line' id='LC82'>&nbsp;&nbsp;&nbsp;<span class="c1">//our own map function, so that we don&#39;t have to get it from some library</span></div><div class='line' id='LC83'>&nbsp;&nbsp;&nbsp;<span class="kt">long</span> <span class="nf">map</span><span class="p">(</span><span class="kt">long</span> <span class="n">x</span><span class="p">,</span> <span class="kt">long</span> <span class="n">in_min</span><span class="p">,</span> <span class="kt">long</span> <span class="n">in_max</span><span class="p">,</span> <span class="kt">long</span> <span class="n">out_min</span><span class="p">,</span> <span class="kt">long</span> <span class="n">out_max</span><span class="p">);</span></div><div class='line' id='LC84'><span class="p">};</span></div><div class='line' id='LC85'><br/></div><div class='line' id='LC86'><span class="cp">#endif</span></div></pre></div>
          </td>
        </tr>
      </table>
  </div>

          </div>
        </div>

        <a href="#jump-to-line" rel="facebox" data-hotkey="l" class="js-jump-to-line" style="display:none">Jump to Line</a>
        <div id="jump-to-line" style="display:none">
          <h2>Jump to Line</h2>
          <form accept-charset="UTF-8" class="js-jump-to-line-form">
            <input class="textfield js-jump-to-line-field" type="text">
            <div class="full-button">
              <button type="submit" class="button">Go</button>
            </div>
          </form>
        </div>

      </div>
    </div>
</div>

<div id="js-frame-loading-template" class="frame frame-loading large-loading-area" style="display:none;">
  <img class="js-frame-loading-spinner" src="https://a248.e.akamai.net/assets.github.com/images/spinners/octocat-spinner-128.gif?1347543527" height="64" width="64">
</div>


        </div>
      </div>
      <div class="context-overlay"></div>
    </div>

      <div id="footer-push"></div><!-- hack for sticky footer -->
    </div><!-- end of wrapper - hack for sticky footer -->

      <!-- footer -->
      <div id="footer">
  <div class="container clearfix">

      <dl class="footer_nav">
        <dt>GitHub</dt>
        <dd><a href="https://github.com/about">About us</a></dd>
        <dd><a href="https://github.com/blog">Blog</a></dd>
        <dd><a href="https://github.com/contact">Contact &amp; support</a></dd>
        <dd><a href="http://enterprise.github.com/">GitHub Enterprise</a></dd>
        <dd><a href="http://status.github.com/">Site status</a></dd>
      </dl>

      <dl class="footer_nav">
        <dt>Applications</dt>
        <dd><a href="http://mac.github.com/">GitHub for Mac</a></dd>
        <dd><a href="http://windows.github.com/">GitHub for Windows</a></dd>
        <dd><a href="http://eclipse.github.com/">GitHub for Eclipse</a></dd>
        <dd><a href="http://mobile.github.com/">GitHub mobile apps</a></dd>
      </dl>

      <dl class="footer_nav">
        <dt>Services</dt>
        <dd><a href="http://get.gaug.es/">Gauges: Web analytics</a></dd>
        <dd><a href="http://speakerdeck.com">Speaker Deck: Presentations</a></dd>
        <dd><a href="https://gist.github.com">Gist: Code snippets</a></dd>
        <dd><a href="http://jobs.github.com/">Job board</a></dd>
      </dl>

      <dl class="footer_nav">
        <dt>Documentation</dt>
        <dd><a href="http://help.github.com/">GitHub Help</a></dd>
        <dd><a href="http://developer.github.com/">Developer API</a></dd>
        <dd><a href="http://github.github.com/github-flavored-markdown/">GitHub Flavored Markdown</a></dd>
        <dd><a href="http://pages.github.com/">GitHub Pages</a></dd>
      </dl>

      <dl class="footer_nav">
        <dt>More</dt>
        <dd><a href="http://training.github.com/">Training</a></dd>
        <dd><a href="https://github.com/edu">Students &amp; teachers</a></dd>
        <dd><a href="http://shop.github.com">The Shop</a></dd>
        <dd><a href="/plans">Plans &amp; pricing</a></dd>
        <dd><a href="http://octodex.github.com/">The Octodex</a></dd>
      </dl>

      <hr class="footer-divider">


    <p class="right">&copy; 2013 <span title="0.08090s from fe18.rs.github.com">GitHub</span>, Inc. All rights reserved.</p>
    <a class="left" href="https://github.com/">
      <span class="mega-icon mega-icon-invertocat"></span>
    </a>
    <ul id="legal">
        <li><a href="https://github.com/site/terms">Terms of Service</a></li>
        <li><a href="https://github.com/site/privacy">Privacy</a></li>
        <li><a href="https://github.com/security">Security</a></li>
    </ul>

  </div><!-- /.container -->

</div><!-- /.#footer -->


    <div class="fullscreen-overlay js-fullscreen-overlay" id="fullscreen_overlay">
  <div class="fullscreen-container js-fullscreen-container">
    <div class="textarea-wrap">
      <textarea name="fullscreen-contents" id="fullscreen-contents" class="js-fullscreen-contents" placeholder="" data-suggester="fullscreen_suggester"></textarea>
          <div class="suggester-container">
              <div class="suggester fullscreen-suggester js-navigation-container" id="fullscreen_suggester"
                 data-url="/fri000/Servo8Bit/suggestions/commit">
              </div>
          </div>
    </div>
  </div>
  <div class="fullscreen-sidebar">
    <a href="#" class="exit-fullscreen js-exit-fullscreen tooltipped leftwards" title="Exit Zen Mode">
      <span class="mega-icon mega-icon-normalscreen"></span>
    </a>
    <a href="#" class="theme-switcher js-theme-switcher tooltipped leftwards"
      title="Switch themes">
      <span class="mini-icon mini-icon-brightness"></span>
    </a>
  </div>
</div>



    <div id="ajax-error-message" class="flash flash-error">
      <span class="mini-icon mini-icon-exclamation"></span>
      Something went wrong with that request. Please try again.
      <a href="#" class="mini-icon mini-icon-remove-close ajax-error-dismiss"></a>
    </div>

    
    
    <span id='server_response_time' data-time='0.08167' data-host='fe18'></span>
    
  </body>
</html>

