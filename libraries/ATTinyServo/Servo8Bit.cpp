  


<!DOCTYPE html>
<html>
  <head prefix="og: http://ogp.me/ns# fb: http://ogp.me/ns/fb# githubog: http://ogp.me/ns/fb/githubog#">
    <meta charset='utf-8'>
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
        <title>Servo8Bit/Servo8Bit.cpp at master · fri000/Servo8Bit · GitHub</title>
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

        <link data-pjax-transient rel='permalink' href='/fri000/Servo8Bit/blob/d5a801c50fe70cb141aa2cbe48f1f12438b61b40/Servo8Bit.cpp'>
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
      <a class="button" href="https://github.com/login?return_to=%2Ffri000%2FServo8Bit%2Fblob%2Fmaster%2FServo8Bit.cpp">Sign in</a>
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
                  <a href="/fri000/Servo8Bit/blob/master/Servo8Bit.cpp" class="js-navigation-open select-menu-item-text js-select-button-text css-truncate-target" data-name="master" rel="nofollow" title="master">master</a>
                </div> <!-- /.select-menu-item -->
            </div>

              <div class="select-menu-no-results">Nothing to show</div>
          </div> <!-- /.select-menu-list -->


          <div class="select-menu-list select-menu-tab-bucket js-select-menu-tab-bucket css-truncate" data-tab-filter="tags">
            <div data-filterable-for="commitish-filter-field" data-filterable-type="substring">

                <div class="select-menu-item js-navigation-item js-navigation-target ">
                  <span class="select-menu-item-icon mini-icon mini-icon-confirm"></span>
                  <a href="/fri000/Servo8Bit/blob/V0.5/Servo8Bit.cpp" class="js-navigation-open select-menu-item-text js-select-button-text css-truncate-target" data-name="V0.5" rel="nofollow" title="V0.5">V0.5</a>
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
          


<!-- blob contrib key: blob_contributors:v21:5880dfb0988f457c17b5db1c0e6e1b40 -->
<!-- blob contrib frag key: views10/v8/blob_contributors:v21:5880dfb0988f457c17b5db1c0e6e1b40 -->


<div id="slider">
    <div class="frame-meta">

      <p title="This is a placeholder element" class="js-history-link-replace hidden"></p>

        <div class="breadcrumb">
          <span class='bold'><span itemscope="" itemtype="http://data-vocabulary.org/Breadcrumb"><a href="/fri000/Servo8Bit" class="js-slide-to" data-branch="master" data-direction="back" itemscope="url"><span itemprop="title">Servo8Bit</span></a></span></span><span class="separator"> / </span><strong class="final-path">Servo8Bit.cpp</strong> <span class="js-zeroclipboard zeroclipboard-button" data-clipboard-text="Servo8Bit.cpp" data-copied-hint="copied!" title="copy to clipboard"><span class="mini-icon mini-icon-clipboard"></span></span>
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
          <a class="avatar tooltipped downwards" title="fri000" href="/fri000/Servo8Bit/commits/master/Servo8Bit.cpp?author=fri000"><img height="20" src="https://secure.gravatar.com/avatar/741bf313a44ebd402ea8ea58e039f111?s=140&amp;d=https://a248.e.akamai.net/assets.github.com%2Fimages%2Fgravatars%2Fgravatar-user-420.png" width="20" /></a>
    <a class="avatar tooltipped downwards" title="justjoheinz" href="/fri000/Servo8Bit/commits/master/Servo8Bit.cpp?author=justjoheinz"><img height="20" src="https://secure.gravatar.com/avatar/02862e49d4152f580a2c81b66d00ea2f?s=140&amp;d=https://a248.e.akamai.net/assets.github.com%2Fimages%2Fgravatars%2Fgravatar-user-420.png" width="20" /></a>


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
      <div class="frame" data-permalink-url="/fri000/Servo8Bit/blob/d5a801c50fe70cb141aa2cbe48f1f12438b61b40/Servo8Bit.cpp" data-title="Servo8Bit/Servo8Bit.cpp at master · fri000/Servo8Bit · GitHub" data-type="blob">

        <div id="files" class="bubble">
          <div class="file">
            <div class="meta">
              <div class="info">
                <span class="icon"><b class="mini-icon mini-icon-text-file"></b></span>
                <span class="mode" title="File Mode">file</span>
                  <span>1005 lines (827 sloc)</span>
                <span>35.049 kb</span>
              </div>
              <div class="actions">
                <div class="button-group">
                      <a class="minibutton js-entice" href=""
                         data-entice="You must be signed in and on a branch to make or propose changes">Edit</a>
                  <a href="/fri000/Servo8Bit/raw/master/Servo8Bit.cpp" class="button minibutton " id="raw-url">Raw</a>
                    <a href="/fri000/Servo8Bit/blame/master/Servo8Bit.cpp" class="button minibutton ">Blame</a>
                  <a href="/fri000/Servo8Bit/commits/master/Servo8Bit.cpp" class="button minibutton " rel="nofollow">History</a>
                </div><!-- /.button-group -->
              </div><!-- /.actions -->

            </div>
                <div class="data type-c js-blob-data">
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
<span id="L87" rel="#L87">87</span>
<span id="L88" rel="#L88">88</span>
<span id="L89" rel="#L89">89</span>
<span id="L90" rel="#L90">90</span>
<span id="L91" rel="#L91">91</span>
<span id="L92" rel="#L92">92</span>
<span id="L93" rel="#L93">93</span>
<span id="L94" rel="#L94">94</span>
<span id="L95" rel="#L95">95</span>
<span id="L96" rel="#L96">96</span>
<span id="L97" rel="#L97">97</span>
<span id="L98" rel="#L98">98</span>
<span id="L99" rel="#L99">99</span>
<span id="L100" rel="#L100">100</span>
<span id="L101" rel="#L101">101</span>
<span id="L102" rel="#L102">102</span>
<span id="L103" rel="#L103">103</span>
<span id="L104" rel="#L104">104</span>
<span id="L105" rel="#L105">105</span>
<span id="L106" rel="#L106">106</span>
<span id="L107" rel="#L107">107</span>
<span id="L108" rel="#L108">108</span>
<span id="L109" rel="#L109">109</span>
<span id="L110" rel="#L110">110</span>
<span id="L111" rel="#L111">111</span>
<span id="L112" rel="#L112">112</span>
<span id="L113" rel="#L113">113</span>
<span id="L114" rel="#L114">114</span>
<span id="L115" rel="#L115">115</span>
<span id="L116" rel="#L116">116</span>
<span id="L117" rel="#L117">117</span>
<span id="L118" rel="#L118">118</span>
<span id="L119" rel="#L119">119</span>
<span id="L120" rel="#L120">120</span>
<span id="L121" rel="#L121">121</span>
<span id="L122" rel="#L122">122</span>
<span id="L123" rel="#L123">123</span>
<span id="L124" rel="#L124">124</span>
<span id="L125" rel="#L125">125</span>
<span id="L126" rel="#L126">126</span>
<span id="L127" rel="#L127">127</span>
<span id="L128" rel="#L128">128</span>
<span id="L129" rel="#L129">129</span>
<span id="L130" rel="#L130">130</span>
<span id="L131" rel="#L131">131</span>
<span id="L132" rel="#L132">132</span>
<span id="L133" rel="#L133">133</span>
<span id="L134" rel="#L134">134</span>
<span id="L135" rel="#L135">135</span>
<span id="L136" rel="#L136">136</span>
<span id="L137" rel="#L137">137</span>
<span id="L138" rel="#L138">138</span>
<span id="L139" rel="#L139">139</span>
<span id="L140" rel="#L140">140</span>
<span id="L141" rel="#L141">141</span>
<span id="L142" rel="#L142">142</span>
<span id="L143" rel="#L143">143</span>
<span id="L144" rel="#L144">144</span>
<span id="L145" rel="#L145">145</span>
<span id="L146" rel="#L146">146</span>
<span id="L147" rel="#L147">147</span>
<span id="L148" rel="#L148">148</span>
<span id="L149" rel="#L149">149</span>
<span id="L150" rel="#L150">150</span>
<span id="L151" rel="#L151">151</span>
<span id="L152" rel="#L152">152</span>
<span id="L153" rel="#L153">153</span>
<span id="L154" rel="#L154">154</span>
<span id="L155" rel="#L155">155</span>
<span id="L156" rel="#L156">156</span>
<span id="L157" rel="#L157">157</span>
<span id="L158" rel="#L158">158</span>
<span id="L159" rel="#L159">159</span>
<span id="L160" rel="#L160">160</span>
<span id="L161" rel="#L161">161</span>
<span id="L162" rel="#L162">162</span>
<span id="L163" rel="#L163">163</span>
<span id="L164" rel="#L164">164</span>
<span id="L165" rel="#L165">165</span>
<span id="L166" rel="#L166">166</span>
<span id="L167" rel="#L167">167</span>
<span id="L168" rel="#L168">168</span>
<span id="L169" rel="#L169">169</span>
<span id="L170" rel="#L170">170</span>
<span id="L171" rel="#L171">171</span>
<span id="L172" rel="#L172">172</span>
<span id="L173" rel="#L173">173</span>
<span id="L174" rel="#L174">174</span>
<span id="L175" rel="#L175">175</span>
<span id="L176" rel="#L176">176</span>
<span id="L177" rel="#L177">177</span>
<span id="L178" rel="#L178">178</span>
<span id="L179" rel="#L179">179</span>
<span id="L180" rel="#L180">180</span>
<span id="L181" rel="#L181">181</span>
<span id="L182" rel="#L182">182</span>
<span id="L183" rel="#L183">183</span>
<span id="L184" rel="#L184">184</span>
<span id="L185" rel="#L185">185</span>
<span id="L186" rel="#L186">186</span>
<span id="L187" rel="#L187">187</span>
<span id="L188" rel="#L188">188</span>
<span id="L189" rel="#L189">189</span>
<span id="L190" rel="#L190">190</span>
<span id="L191" rel="#L191">191</span>
<span id="L192" rel="#L192">192</span>
<span id="L193" rel="#L193">193</span>
<span id="L194" rel="#L194">194</span>
<span id="L195" rel="#L195">195</span>
<span id="L196" rel="#L196">196</span>
<span id="L197" rel="#L197">197</span>
<span id="L198" rel="#L198">198</span>
<span id="L199" rel="#L199">199</span>
<span id="L200" rel="#L200">200</span>
<span id="L201" rel="#L201">201</span>
<span id="L202" rel="#L202">202</span>
<span id="L203" rel="#L203">203</span>
<span id="L204" rel="#L204">204</span>
<span id="L205" rel="#L205">205</span>
<span id="L206" rel="#L206">206</span>
<span id="L207" rel="#L207">207</span>
<span id="L208" rel="#L208">208</span>
<span id="L209" rel="#L209">209</span>
<span id="L210" rel="#L210">210</span>
<span id="L211" rel="#L211">211</span>
<span id="L212" rel="#L212">212</span>
<span id="L213" rel="#L213">213</span>
<span id="L214" rel="#L214">214</span>
<span id="L215" rel="#L215">215</span>
<span id="L216" rel="#L216">216</span>
<span id="L217" rel="#L217">217</span>
<span id="L218" rel="#L218">218</span>
<span id="L219" rel="#L219">219</span>
<span id="L220" rel="#L220">220</span>
<span id="L221" rel="#L221">221</span>
<span id="L222" rel="#L222">222</span>
<span id="L223" rel="#L223">223</span>
<span id="L224" rel="#L224">224</span>
<span id="L225" rel="#L225">225</span>
<span id="L226" rel="#L226">226</span>
<span id="L227" rel="#L227">227</span>
<span id="L228" rel="#L228">228</span>
<span id="L229" rel="#L229">229</span>
<span id="L230" rel="#L230">230</span>
<span id="L231" rel="#L231">231</span>
<span id="L232" rel="#L232">232</span>
<span id="L233" rel="#L233">233</span>
<span id="L234" rel="#L234">234</span>
<span id="L235" rel="#L235">235</span>
<span id="L236" rel="#L236">236</span>
<span id="L237" rel="#L237">237</span>
<span id="L238" rel="#L238">238</span>
<span id="L239" rel="#L239">239</span>
<span id="L240" rel="#L240">240</span>
<span id="L241" rel="#L241">241</span>
<span id="L242" rel="#L242">242</span>
<span id="L243" rel="#L243">243</span>
<span id="L244" rel="#L244">244</span>
<span id="L245" rel="#L245">245</span>
<span id="L246" rel="#L246">246</span>
<span id="L247" rel="#L247">247</span>
<span id="L248" rel="#L248">248</span>
<span id="L249" rel="#L249">249</span>
<span id="L250" rel="#L250">250</span>
<span id="L251" rel="#L251">251</span>
<span id="L252" rel="#L252">252</span>
<span id="L253" rel="#L253">253</span>
<span id="L254" rel="#L254">254</span>
<span id="L255" rel="#L255">255</span>
<span id="L256" rel="#L256">256</span>
<span id="L257" rel="#L257">257</span>
<span id="L258" rel="#L258">258</span>
<span id="L259" rel="#L259">259</span>
<span id="L260" rel="#L260">260</span>
<span id="L261" rel="#L261">261</span>
<span id="L262" rel="#L262">262</span>
<span id="L263" rel="#L263">263</span>
<span id="L264" rel="#L264">264</span>
<span id="L265" rel="#L265">265</span>
<span id="L266" rel="#L266">266</span>
<span id="L267" rel="#L267">267</span>
<span id="L268" rel="#L268">268</span>
<span id="L269" rel="#L269">269</span>
<span id="L270" rel="#L270">270</span>
<span id="L271" rel="#L271">271</span>
<span id="L272" rel="#L272">272</span>
<span id="L273" rel="#L273">273</span>
<span id="L274" rel="#L274">274</span>
<span id="L275" rel="#L275">275</span>
<span id="L276" rel="#L276">276</span>
<span id="L277" rel="#L277">277</span>
<span id="L278" rel="#L278">278</span>
<span id="L279" rel="#L279">279</span>
<span id="L280" rel="#L280">280</span>
<span id="L281" rel="#L281">281</span>
<span id="L282" rel="#L282">282</span>
<span id="L283" rel="#L283">283</span>
<span id="L284" rel="#L284">284</span>
<span id="L285" rel="#L285">285</span>
<span id="L286" rel="#L286">286</span>
<span id="L287" rel="#L287">287</span>
<span id="L288" rel="#L288">288</span>
<span id="L289" rel="#L289">289</span>
<span id="L290" rel="#L290">290</span>
<span id="L291" rel="#L291">291</span>
<span id="L292" rel="#L292">292</span>
<span id="L293" rel="#L293">293</span>
<span id="L294" rel="#L294">294</span>
<span id="L295" rel="#L295">295</span>
<span id="L296" rel="#L296">296</span>
<span id="L297" rel="#L297">297</span>
<span id="L298" rel="#L298">298</span>
<span id="L299" rel="#L299">299</span>
<span id="L300" rel="#L300">300</span>
<span id="L301" rel="#L301">301</span>
<span id="L302" rel="#L302">302</span>
<span id="L303" rel="#L303">303</span>
<span id="L304" rel="#L304">304</span>
<span id="L305" rel="#L305">305</span>
<span id="L306" rel="#L306">306</span>
<span id="L307" rel="#L307">307</span>
<span id="L308" rel="#L308">308</span>
<span id="L309" rel="#L309">309</span>
<span id="L310" rel="#L310">310</span>
<span id="L311" rel="#L311">311</span>
<span id="L312" rel="#L312">312</span>
<span id="L313" rel="#L313">313</span>
<span id="L314" rel="#L314">314</span>
<span id="L315" rel="#L315">315</span>
<span id="L316" rel="#L316">316</span>
<span id="L317" rel="#L317">317</span>
<span id="L318" rel="#L318">318</span>
<span id="L319" rel="#L319">319</span>
<span id="L320" rel="#L320">320</span>
<span id="L321" rel="#L321">321</span>
<span id="L322" rel="#L322">322</span>
<span id="L323" rel="#L323">323</span>
<span id="L324" rel="#L324">324</span>
<span id="L325" rel="#L325">325</span>
<span id="L326" rel="#L326">326</span>
<span id="L327" rel="#L327">327</span>
<span id="L328" rel="#L328">328</span>
<span id="L329" rel="#L329">329</span>
<span id="L330" rel="#L330">330</span>
<span id="L331" rel="#L331">331</span>
<span id="L332" rel="#L332">332</span>
<span id="L333" rel="#L333">333</span>
<span id="L334" rel="#L334">334</span>
<span id="L335" rel="#L335">335</span>
<span id="L336" rel="#L336">336</span>
<span id="L337" rel="#L337">337</span>
<span id="L338" rel="#L338">338</span>
<span id="L339" rel="#L339">339</span>
<span id="L340" rel="#L340">340</span>
<span id="L341" rel="#L341">341</span>
<span id="L342" rel="#L342">342</span>
<span id="L343" rel="#L343">343</span>
<span id="L344" rel="#L344">344</span>
<span id="L345" rel="#L345">345</span>
<span id="L346" rel="#L346">346</span>
<span id="L347" rel="#L347">347</span>
<span id="L348" rel="#L348">348</span>
<span id="L349" rel="#L349">349</span>
<span id="L350" rel="#L350">350</span>
<span id="L351" rel="#L351">351</span>
<span id="L352" rel="#L352">352</span>
<span id="L353" rel="#L353">353</span>
<span id="L354" rel="#L354">354</span>
<span id="L355" rel="#L355">355</span>
<span id="L356" rel="#L356">356</span>
<span id="L357" rel="#L357">357</span>
<span id="L358" rel="#L358">358</span>
<span id="L359" rel="#L359">359</span>
<span id="L360" rel="#L360">360</span>
<span id="L361" rel="#L361">361</span>
<span id="L362" rel="#L362">362</span>
<span id="L363" rel="#L363">363</span>
<span id="L364" rel="#L364">364</span>
<span id="L365" rel="#L365">365</span>
<span id="L366" rel="#L366">366</span>
<span id="L367" rel="#L367">367</span>
<span id="L368" rel="#L368">368</span>
<span id="L369" rel="#L369">369</span>
<span id="L370" rel="#L370">370</span>
<span id="L371" rel="#L371">371</span>
<span id="L372" rel="#L372">372</span>
<span id="L373" rel="#L373">373</span>
<span id="L374" rel="#L374">374</span>
<span id="L375" rel="#L375">375</span>
<span id="L376" rel="#L376">376</span>
<span id="L377" rel="#L377">377</span>
<span id="L378" rel="#L378">378</span>
<span id="L379" rel="#L379">379</span>
<span id="L380" rel="#L380">380</span>
<span id="L381" rel="#L381">381</span>
<span id="L382" rel="#L382">382</span>
<span id="L383" rel="#L383">383</span>
<span id="L384" rel="#L384">384</span>
<span id="L385" rel="#L385">385</span>
<span id="L386" rel="#L386">386</span>
<span id="L387" rel="#L387">387</span>
<span id="L388" rel="#L388">388</span>
<span id="L389" rel="#L389">389</span>
<span id="L390" rel="#L390">390</span>
<span id="L391" rel="#L391">391</span>
<span id="L392" rel="#L392">392</span>
<span id="L393" rel="#L393">393</span>
<span id="L394" rel="#L394">394</span>
<span id="L395" rel="#L395">395</span>
<span id="L396" rel="#L396">396</span>
<span id="L397" rel="#L397">397</span>
<span id="L398" rel="#L398">398</span>
<span id="L399" rel="#L399">399</span>
<span id="L400" rel="#L400">400</span>
<span id="L401" rel="#L401">401</span>
<span id="L402" rel="#L402">402</span>
<span id="L403" rel="#L403">403</span>
<span id="L404" rel="#L404">404</span>
<span id="L405" rel="#L405">405</span>
<span id="L406" rel="#L406">406</span>
<span id="L407" rel="#L407">407</span>
<span id="L408" rel="#L408">408</span>
<span id="L409" rel="#L409">409</span>
<span id="L410" rel="#L410">410</span>
<span id="L411" rel="#L411">411</span>
<span id="L412" rel="#L412">412</span>
<span id="L413" rel="#L413">413</span>
<span id="L414" rel="#L414">414</span>
<span id="L415" rel="#L415">415</span>
<span id="L416" rel="#L416">416</span>
<span id="L417" rel="#L417">417</span>
<span id="L418" rel="#L418">418</span>
<span id="L419" rel="#L419">419</span>
<span id="L420" rel="#L420">420</span>
<span id="L421" rel="#L421">421</span>
<span id="L422" rel="#L422">422</span>
<span id="L423" rel="#L423">423</span>
<span id="L424" rel="#L424">424</span>
<span id="L425" rel="#L425">425</span>
<span id="L426" rel="#L426">426</span>
<span id="L427" rel="#L427">427</span>
<span id="L428" rel="#L428">428</span>
<span id="L429" rel="#L429">429</span>
<span id="L430" rel="#L430">430</span>
<span id="L431" rel="#L431">431</span>
<span id="L432" rel="#L432">432</span>
<span id="L433" rel="#L433">433</span>
<span id="L434" rel="#L434">434</span>
<span id="L435" rel="#L435">435</span>
<span id="L436" rel="#L436">436</span>
<span id="L437" rel="#L437">437</span>
<span id="L438" rel="#L438">438</span>
<span id="L439" rel="#L439">439</span>
<span id="L440" rel="#L440">440</span>
<span id="L441" rel="#L441">441</span>
<span id="L442" rel="#L442">442</span>
<span id="L443" rel="#L443">443</span>
<span id="L444" rel="#L444">444</span>
<span id="L445" rel="#L445">445</span>
<span id="L446" rel="#L446">446</span>
<span id="L447" rel="#L447">447</span>
<span id="L448" rel="#L448">448</span>
<span id="L449" rel="#L449">449</span>
<span id="L450" rel="#L450">450</span>
<span id="L451" rel="#L451">451</span>
<span id="L452" rel="#L452">452</span>
<span id="L453" rel="#L453">453</span>
<span id="L454" rel="#L454">454</span>
<span id="L455" rel="#L455">455</span>
<span id="L456" rel="#L456">456</span>
<span id="L457" rel="#L457">457</span>
<span id="L458" rel="#L458">458</span>
<span id="L459" rel="#L459">459</span>
<span id="L460" rel="#L460">460</span>
<span id="L461" rel="#L461">461</span>
<span id="L462" rel="#L462">462</span>
<span id="L463" rel="#L463">463</span>
<span id="L464" rel="#L464">464</span>
<span id="L465" rel="#L465">465</span>
<span id="L466" rel="#L466">466</span>
<span id="L467" rel="#L467">467</span>
<span id="L468" rel="#L468">468</span>
<span id="L469" rel="#L469">469</span>
<span id="L470" rel="#L470">470</span>
<span id="L471" rel="#L471">471</span>
<span id="L472" rel="#L472">472</span>
<span id="L473" rel="#L473">473</span>
<span id="L474" rel="#L474">474</span>
<span id="L475" rel="#L475">475</span>
<span id="L476" rel="#L476">476</span>
<span id="L477" rel="#L477">477</span>
<span id="L478" rel="#L478">478</span>
<span id="L479" rel="#L479">479</span>
<span id="L480" rel="#L480">480</span>
<span id="L481" rel="#L481">481</span>
<span id="L482" rel="#L482">482</span>
<span id="L483" rel="#L483">483</span>
<span id="L484" rel="#L484">484</span>
<span id="L485" rel="#L485">485</span>
<span id="L486" rel="#L486">486</span>
<span id="L487" rel="#L487">487</span>
<span id="L488" rel="#L488">488</span>
<span id="L489" rel="#L489">489</span>
<span id="L490" rel="#L490">490</span>
<span id="L491" rel="#L491">491</span>
<span id="L492" rel="#L492">492</span>
<span id="L493" rel="#L493">493</span>
<span id="L494" rel="#L494">494</span>
<span id="L495" rel="#L495">495</span>
<span id="L496" rel="#L496">496</span>
<span id="L497" rel="#L497">497</span>
<span id="L498" rel="#L498">498</span>
<span id="L499" rel="#L499">499</span>
<span id="L500" rel="#L500">500</span>
<span id="L501" rel="#L501">501</span>
<span id="L502" rel="#L502">502</span>
<span id="L503" rel="#L503">503</span>
<span id="L504" rel="#L504">504</span>
<span id="L505" rel="#L505">505</span>
<span id="L506" rel="#L506">506</span>
<span id="L507" rel="#L507">507</span>
<span id="L508" rel="#L508">508</span>
<span id="L509" rel="#L509">509</span>
<span id="L510" rel="#L510">510</span>
<span id="L511" rel="#L511">511</span>
<span id="L512" rel="#L512">512</span>
<span id="L513" rel="#L513">513</span>
<span id="L514" rel="#L514">514</span>
<span id="L515" rel="#L515">515</span>
<span id="L516" rel="#L516">516</span>
<span id="L517" rel="#L517">517</span>
<span id="L518" rel="#L518">518</span>
<span id="L519" rel="#L519">519</span>
<span id="L520" rel="#L520">520</span>
<span id="L521" rel="#L521">521</span>
<span id="L522" rel="#L522">522</span>
<span id="L523" rel="#L523">523</span>
<span id="L524" rel="#L524">524</span>
<span id="L525" rel="#L525">525</span>
<span id="L526" rel="#L526">526</span>
<span id="L527" rel="#L527">527</span>
<span id="L528" rel="#L528">528</span>
<span id="L529" rel="#L529">529</span>
<span id="L530" rel="#L530">530</span>
<span id="L531" rel="#L531">531</span>
<span id="L532" rel="#L532">532</span>
<span id="L533" rel="#L533">533</span>
<span id="L534" rel="#L534">534</span>
<span id="L535" rel="#L535">535</span>
<span id="L536" rel="#L536">536</span>
<span id="L537" rel="#L537">537</span>
<span id="L538" rel="#L538">538</span>
<span id="L539" rel="#L539">539</span>
<span id="L540" rel="#L540">540</span>
<span id="L541" rel="#L541">541</span>
<span id="L542" rel="#L542">542</span>
<span id="L543" rel="#L543">543</span>
<span id="L544" rel="#L544">544</span>
<span id="L545" rel="#L545">545</span>
<span id="L546" rel="#L546">546</span>
<span id="L547" rel="#L547">547</span>
<span id="L548" rel="#L548">548</span>
<span id="L549" rel="#L549">549</span>
<span id="L550" rel="#L550">550</span>
<span id="L551" rel="#L551">551</span>
<span id="L552" rel="#L552">552</span>
<span id="L553" rel="#L553">553</span>
<span id="L554" rel="#L554">554</span>
<span id="L555" rel="#L555">555</span>
<span id="L556" rel="#L556">556</span>
<span id="L557" rel="#L557">557</span>
<span id="L558" rel="#L558">558</span>
<span id="L559" rel="#L559">559</span>
<span id="L560" rel="#L560">560</span>
<span id="L561" rel="#L561">561</span>
<span id="L562" rel="#L562">562</span>
<span id="L563" rel="#L563">563</span>
<span id="L564" rel="#L564">564</span>
<span id="L565" rel="#L565">565</span>
<span id="L566" rel="#L566">566</span>
<span id="L567" rel="#L567">567</span>
<span id="L568" rel="#L568">568</span>
<span id="L569" rel="#L569">569</span>
<span id="L570" rel="#L570">570</span>
<span id="L571" rel="#L571">571</span>
<span id="L572" rel="#L572">572</span>
<span id="L573" rel="#L573">573</span>
<span id="L574" rel="#L574">574</span>
<span id="L575" rel="#L575">575</span>
<span id="L576" rel="#L576">576</span>
<span id="L577" rel="#L577">577</span>
<span id="L578" rel="#L578">578</span>
<span id="L579" rel="#L579">579</span>
<span id="L580" rel="#L580">580</span>
<span id="L581" rel="#L581">581</span>
<span id="L582" rel="#L582">582</span>
<span id="L583" rel="#L583">583</span>
<span id="L584" rel="#L584">584</span>
<span id="L585" rel="#L585">585</span>
<span id="L586" rel="#L586">586</span>
<span id="L587" rel="#L587">587</span>
<span id="L588" rel="#L588">588</span>
<span id="L589" rel="#L589">589</span>
<span id="L590" rel="#L590">590</span>
<span id="L591" rel="#L591">591</span>
<span id="L592" rel="#L592">592</span>
<span id="L593" rel="#L593">593</span>
<span id="L594" rel="#L594">594</span>
<span id="L595" rel="#L595">595</span>
<span id="L596" rel="#L596">596</span>
<span id="L597" rel="#L597">597</span>
<span id="L598" rel="#L598">598</span>
<span id="L599" rel="#L599">599</span>
<span id="L600" rel="#L600">600</span>
<span id="L601" rel="#L601">601</span>
<span id="L602" rel="#L602">602</span>
<span id="L603" rel="#L603">603</span>
<span id="L604" rel="#L604">604</span>
<span id="L605" rel="#L605">605</span>
<span id="L606" rel="#L606">606</span>
<span id="L607" rel="#L607">607</span>
<span id="L608" rel="#L608">608</span>
<span id="L609" rel="#L609">609</span>
<span id="L610" rel="#L610">610</span>
<span id="L611" rel="#L611">611</span>
<span id="L612" rel="#L612">612</span>
<span id="L613" rel="#L613">613</span>
<span id="L614" rel="#L614">614</span>
<span id="L615" rel="#L615">615</span>
<span id="L616" rel="#L616">616</span>
<span id="L617" rel="#L617">617</span>
<span id="L618" rel="#L618">618</span>
<span id="L619" rel="#L619">619</span>
<span id="L620" rel="#L620">620</span>
<span id="L621" rel="#L621">621</span>
<span id="L622" rel="#L622">622</span>
<span id="L623" rel="#L623">623</span>
<span id="L624" rel="#L624">624</span>
<span id="L625" rel="#L625">625</span>
<span id="L626" rel="#L626">626</span>
<span id="L627" rel="#L627">627</span>
<span id="L628" rel="#L628">628</span>
<span id="L629" rel="#L629">629</span>
<span id="L630" rel="#L630">630</span>
<span id="L631" rel="#L631">631</span>
<span id="L632" rel="#L632">632</span>
<span id="L633" rel="#L633">633</span>
<span id="L634" rel="#L634">634</span>
<span id="L635" rel="#L635">635</span>
<span id="L636" rel="#L636">636</span>
<span id="L637" rel="#L637">637</span>
<span id="L638" rel="#L638">638</span>
<span id="L639" rel="#L639">639</span>
<span id="L640" rel="#L640">640</span>
<span id="L641" rel="#L641">641</span>
<span id="L642" rel="#L642">642</span>
<span id="L643" rel="#L643">643</span>
<span id="L644" rel="#L644">644</span>
<span id="L645" rel="#L645">645</span>
<span id="L646" rel="#L646">646</span>
<span id="L647" rel="#L647">647</span>
<span id="L648" rel="#L648">648</span>
<span id="L649" rel="#L649">649</span>
<span id="L650" rel="#L650">650</span>
<span id="L651" rel="#L651">651</span>
<span id="L652" rel="#L652">652</span>
<span id="L653" rel="#L653">653</span>
<span id="L654" rel="#L654">654</span>
<span id="L655" rel="#L655">655</span>
<span id="L656" rel="#L656">656</span>
<span id="L657" rel="#L657">657</span>
<span id="L658" rel="#L658">658</span>
<span id="L659" rel="#L659">659</span>
<span id="L660" rel="#L660">660</span>
<span id="L661" rel="#L661">661</span>
<span id="L662" rel="#L662">662</span>
<span id="L663" rel="#L663">663</span>
<span id="L664" rel="#L664">664</span>
<span id="L665" rel="#L665">665</span>
<span id="L666" rel="#L666">666</span>
<span id="L667" rel="#L667">667</span>
<span id="L668" rel="#L668">668</span>
<span id="L669" rel="#L669">669</span>
<span id="L670" rel="#L670">670</span>
<span id="L671" rel="#L671">671</span>
<span id="L672" rel="#L672">672</span>
<span id="L673" rel="#L673">673</span>
<span id="L674" rel="#L674">674</span>
<span id="L675" rel="#L675">675</span>
<span id="L676" rel="#L676">676</span>
<span id="L677" rel="#L677">677</span>
<span id="L678" rel="#L678">678</span>
<span id="L679" rel="#L679">679</span>
<span id="L680" rel="#L680">680</span>
<span id="L681" rel="#L681">681</span>
<span id="L682" rel="#L682">682</span>
<span id="L683" rel="#L683">683</span>
<span id="L684" rel="#L684">684</span>
<span id="L685" rel="#L685">685</span>
<span id="L686" rel="#L686">686</span>
<span id="L687" rel="#L687">687</span>
<span id="L688" rel="#L688">688</span>
<span id="L689" rel="#L689">689</span>
<span id="L690" rel="#L690">690</span>
<span id="L691" rel="#L691">691</span>
<span id="L692" rel="#L692">692</span>
<span id="L693" rel="#L693">693</span>
<span id="L694" rel="#L694">694</span>
<span id="L695" rel="#L695">695</span>
<span id="L696" rel="#L696">696</span>
<span id="L697" rel="#L697">697</span>
<span id="L698" rel="#L698">698</span>
<span id="L699" rel="#L699">699</span>
<span id="L700" rel="#L700">700</span>
<span id="L701" rel="#L701">701</span>
<span id="L702" rel="#L702">702</span>
<span id="L703" rel="#L703">703</span>
<span id="L704" rel="#L704">704</span>
<span id="L705" rel="#L705">705</span>
<span id="L706" rel="#L706">706</span>
<span id="L707" rel="#L707">707</span>
<span id="L708" rel="#L708">708</span>
<span id="L709" rel="#L709">709</span>
<span id="L710" rel="#L710">710</span>
<span id="L711" rel="#L711">711</span>
<span id="L712" rel="#L712">712</span>
<span id="L713" rel="#L713">713</span>
<span id="L714" rel="#L714">714</span>
<span id="L715" rel="#L715">715</span>
<span id="L716" rel="#L716">716</span>
<span id="L717" rel="#L717">717</span>
<span id="L718" rel="#L718">718</span>
<span id="L719" rel="#L719">719</span>
<span id="L720" rel="#L720">720</span>
<span id="L721" rel="#L721">721</span>
<span id="L722" rel="#L722">722</span>
<span id="L723" rel="#L723">723</span>
<span id="L724" rel="#L724">724</span>
<span id="L725" rel="#L725">725</span>
<span id="L726" rel="#L726">726</span>
<span id="L727" rel="#L727">727</span>
<span id="L728" rel="#L728">728</span>
<span id="L729" rel="#L729">729</span>
<span id="L730" rel="#L730">730</span>
<span id="L731" rel="#L731">731</span>
<span id="L732" rel="#L732">732</span>
<span id="L733" rel="#L733">733</span>
<span id="L734" rel="#L734">734</span>
<span id="L735" rel="#L735">735</span>
<span id="L736" rel="#L736">736</span>
<span id="L737" rel="#L737">737</span>
<span id="L738" rel="#L738">738</span>
<span id="L739" rel="#L739">739</span>
<span id="L740" rel="#L740">740</span>
<span id="L741" rel="#L741">741</span>
<span id="L742" rel="#L742">742</span>
<span id="L743" rel="#L743">743</span>
<span id="L744" rel="#L744">744</span>
<span id="L745" rel="#L745">745</span>
<span id="L746" rel="#L746">746</span>
<span id="L747" rel="#L747">747</span>
<span id="L748" rel="#L748">748</span>
<span id="L749" rel="#L749">749</span>
<span id="L750" rel="#L750">750</span>
<span id="L751" rel="#L751">751</span>
<span id="L752" rel="#L752">752</span>
<span id="L753" rel="#L753">753</span>
<span id="L754" rel="#L754">754</span>
<span id="L755" rel="#L755">755</span>
<span id="L756" rel="#L756">756</span>
<span id="L757" rel="#L757">757</span>
<span id="L758" rel="#L758">758</span>
<span id="L759" rel="#L759">759</span>
<span id="L760" rel="#L760">760</span>
<span id="L761" rel="#L761">761</span>
<span id="L762" rel="#L762">762</span>
<span id="L763" rel="#L763">763</span>
<span id="L764" rel="#L764">764</span>
<span id="L765" rel="#L765">765</span>
<span id="L766" rel="#L766">766</span>
<span id="L767" rel="#L767">767</span>
<span id="L768" rel="#L768">768</span>
<span id="L769" rel="#L769">769</span>
<span id="L770" rel="#L770">770</span>
<span id="L771" rel="#L771">771</span>
<span id="L772" rel="#L772">772</span>
<span id="L773" rel="#L773">773</span>
<span id="L774" rel="#L774">774</span>
<span id="L775" rel="#L775">775</span>
<span id="L776" rel="#L776">776</span>
<span id="L777" rel="#L777">777</span>
<span id="L778" rel="#L778">778</span>
<span id="L779" rel="#L779">779</span>
<span id="L780" rel="#L780">780</span>
<span id="L781" rel="#L781">781</span>
<span id="L782" rel="#L782">782</span>
<span id="L783" rel="#L783">783</span>
<span id="L784" rel="#L784">784</span>
<span id="L785" rel="#L785">785</span>
<span id="L786" rel="#L786">786</span>
<span id="L787" rel="#L787">787</span>
<span id="L788" rel="#L788">788</span>
<span id="L789" rel="#L789">789</span>
<span id="L790" rel="#L790">790</span>
<span id="L791" rel="#L791">791</span>
<span id="L792" rel="#L792">792</span>
<span id="L793" rel="#L793">793</span>
<span id="L794" rel="#L794">794</span>
<span id="L795" rel="#L795">795</span>
<span id="L796" rel="#L796">796</span>
<span id="L797" rel="#L797">797</span>
<span id="L798" rel="#L798">798</span>
<span id="L799" rel="#L799">799</span>
<span id="L800" rel="#L800">800</span>
<span id="L801" rel="#L801">801</span>
<span id="L802" rel="#L802">802</span>
<span id="L803" rel="#L803">803</span>
<span id="L804" rel="#L804">804</span>
<span id="L805" rel="#L805">805</span>
<span id="L806" rel="#L806">806</span>
<span id="L807" rel="#L807">807</span>
<span id="L808" rel="#L808">808</span>
<span id="L809" rel="#L809">809</span>
<span id="L810" rel="#L810">810</span>
<span id="L811" rel="#L811">811</span>
<span id="L812" rel="#L812">812</span>
<span id="L813" rel="#L813">813</span>
<span id="L814" rel="#L814">814</span>
<span id="L815" rel="#L815">815</span>
<span id="L816" rel="#L816">816</span>
<span id="L817" rel="#L817">817</span>
<span id="L818" rel="#L818">818</span>
<span id="L819" rel="#L819">819</span>
<span id="L820" rel="#L820">820</span>
<span id="L821" rel="#L821">821</span>
<span id="L822" rel="#L822">822</span>
<span id="L823" rel="#L823">823</span>
<span id="L824" rel="#L824">824</span>
<span id="L825" rel="#L825">825</span>
<span id="L826" rel="#L826">826</span>
<span id="L827" rel="#L827">827</span>
<span id="L828" rel="#L828">828</span>
<span id="L829" rel="#L829">829</span>
<span id="L830" rel="#L830">830</span>
<span id="L831" rel="#L831">831</span>
<span id="L832" rel="#L832">832</span>
<span id="L833" rel="#L833">833</span>
<span id="L834" rel="#L834">834</span>
<span id="L835" rel="#L835">835</span>
<span id="L836" rel="#L836">836</span>
<span id="L837" rel="#L837">837</span>
<span id="L838" rel="#L838">838</span>
<span id="L839" rel="#L839">839</span>
<span id="L840" rel="#L840">840</span>
<span id="L841" rel="#L841">841</span>
<span id="L842" rel="#L842">842</span>
<span id="L843" rel="#L843">843</span>
<span id="L844" rel="#L844">844</span>
<span id="L845" rel="#L845">845</span>
<span id="L846" rel="#L846">846</span>
<span id="L847" rel="#L847">847</span>
<span id="L848" rel="#L848">848</span>
<span id="L849" rel="#L849">849</span>
<span id="L850" rel="#L850">850</span>
<span id="L851" rel="#L851">851</span>
<span id="L852" rel="#L852">852</span>
<span id="L853" rel="#L853">853</span>
<span id="L854" rel="#L854">854</span>
<span id="L855" rel="#L855">855</span>
<span id="L856" rel="#L856">856</span>
<span id="L857" rel="#L857">857</span>
<span id="L858" rel="#L858">858</span>
<span id="L859" rel="#L859">859</span>
<span id="L860" rel="#L860">860</span>
<span id="L861" rel="#L861">861</span>
<span id="L862" rel="#L862">862</span>
<span id="L863" rel="#L863">863</span>
<span id="L864" rel="#L864">864</span>
<span id="L865" rel="#L865">865</span>
<span id="L866" rel="#L866">866</span>
<span id="L867" rel="#L867">867</span>
<span id="L868" rel="#L868">868</span>
<span id="L869" rel="#L869">869</span>
<span id="L870" rel="#L870">870</span>
<span id="L871" rel="#L871">871</span>
<span id="L872" rel="#L872">872</span>
<span id="L873" rel="#L873">873</span>
<span id="L874" rel="#L874">874</span>
<span id="L875" rel="#L875">875</span>
<span id="L876" rel="#L876">876</span>
<span id="L877" rel="#L877">877</span>
<span id="L878" rel="#L878">878</span>
<span id="L879" rel="#L879">879</span>
<span id="L880" rel="#L880">880</span>
<span id="L881" rel="#L881">881</span>
<span id="L882" rel="#L882">882</span>
<span id="L883" rel="#L883">883</span>
<span id="L884" rel="#L884">884</span>
<span id="L885" rel="#L885">885</span>
<span id="L886" rel="#L886">886</span>
<span id="L887" rel="#L887">887</span>
<span id="L888" rel="#L888">888</span>
<span id="L889" rel="#L889">889</span>
<span id="L890" rel="#L890">890</span>
<span id="L891" rel="#L891">891</span>
<span id="L892" rel="#L892">892</span>
<span id="L893" rel="#L893">893</span>
<span id="L894" rel="#L894">894</span>
<span id="L895" rel="#L895">895</span>
<span id="L896" rel="#L896">896</span>
<span id="L897" rel="#L897">897</span>
<span id="L898" rel="#L898">898</span>
<span id="L899" rel="#L899">899</span>
<span id="L900" rel="#L900">900</span>
<span id="L901" rel="#L901">901</span>
<span id="L902" rel="#L902">902</span>
<span id="L903" rel="#L903">903</span>
<span id="L904" rel="#L904">904</span>
<span id="L905" rel="#L905">905</span>
<span id="L906" rel="#L906">906</span>
<span id="L907" rel="#L907">907</span>
<span id="L908" rel="#L908">908</span>
<span id="L909" rel="#L909">909</span>
<span id="L910" rel="#L910">910</span>
<span id="L911" rel="#L911">911</span>
<span id="L912" rel="#L912">912</span>
<span id="L913" rel="#L913">913</span>
<span id="L914" rel="#L914">914</span>
<span id="L915" rel="#L915">915</span>
<span id="L916" rel="#L916">916</span>
<span id="L917" rel="#L917">917</span>
<span id="L918" rel="#L918">918</span>
<span id="L919" rel="#L919">919</span>
<span id="L920" rel="#L920">920</span>
<span id="L921" rel="#L921">921</span>
<span id="L922" rel="#L922">922</span>
<span id="L923" rel="#L923">923</span>
<span id="L924" rel="#L924">924</span>
<span id="L925" rel="#L925">925</span>
<span id="L926" rel="#L926">926</span>
<span id="L927" rel="#L927">927</span>
<span id="L928" rel="#L928">928</span>
<span id="L929" rel="#L929">929</span>
<span id="L930" rel="#L930">930</span>
<span id="L931" rel="#L931">931</span>
<span id="L932" rel="#L932">932</span>
<span id="L933" rel="#L933">933</span>
<span id="L934" rel="#L934">934</span>
<span id="L935" rel="#L935">935</span>
<span id="L936" rel="#L936">936</span>
<span id="L937" rel="#L937">937</span>
<span id="L938" rel="#L938">938</span>
<span id="L939" rel="#L939">939</span>
<span id="L940" rel="#L940">940</span>
<span id="L941" rel="#L941">941</span>
<span id="L942" rel="#L942">942</span>
<span id="L943" rel="#L943">943</span>
<span id="L944" rel="#L944">944</span>
<span id="L945" rel="#L945">945</span>
<span id="L946" rel="#L946">946</span>
<span id="L947" rel="#L947">947</span>
<span id="L948" rel="#L948">948</span>
<span id="L949" rel="#L949">949</span>
<span id="L950" rel="#L950">950</span>
<span id="L951" rel="#L951">951</span>
<span id="L952" rel="#L952">952</span>
<span id="L953" rel="#L953">953</span>
<span id="L954" rel="#L954">954</span>
<span id="L955" rel="#L955">955</span>
<span id="L956" rel="#L956">956</span>
<span id="L957" rel="#L957">957</span>
<span id="L958" rel="#L958">958</span>
<span id="L959" rel="#L959">959</span>
<span id="L960" rel="#L960">960</span>
<span id="L961" rel="#L961">961</span>
<span id="L962" rel="#L962">962</span>
<span id="L963" rel="#L963">963</span>
<span id="L964" rel="#L964">964</span>
<span id="L965" rel="#L965">965</span>
<span id="L966" rel="#L966">966</span>
<span id="L967" rel="#L967">967</span>
<span id="L968" rel="#L968">968</span>
<span id="L969" rel="#L969">969</span>
<span id="L970" rel="#L970">970</span>
<span id="L971" rel="#L971">971</span>
<span id="L972" rel="#L972">972</span>
<span id="L973" rel="#L973">973</span>
<span id="L974" rel="#L974">974</span>
<span id="L975" rel="#L975">975</span>
<span id="L976" rel="#L976">976</span>
<span id="L977" rel="#L977">977</span>
<span id="L978" rel="#L978">978</span>
<span id="L979" rel="#L979">979</span>
<span id="L980" rel="#L980">980</span>
<span id="L981" rel="#L981">981</span>
<span id="L982" rel="#L982">982</span>
<span id="L983" rel="#L983">983</span>
<span id="L984" rel="#L984">984</span>
<span id="L985" rel="#L985">985</span>
<span id="L986" rel="#L986">986</span>
<span id="L987" rel="#L987">987</span>
<span id="L988" rel="#L988">988</span>
<span id="L989" rel="#L989">989</span>
<span id="L990" rel="#L990">990</span>
<span id="L991" rel="#L991">991</span>
<span id="L992" rel="#L992">992</span>
<span id="L993" rel="#L993">993</span>
<span id="L994" rel="#L994">994</span>
<span id="L995" rel="#L995">995</span>
<span id="L996" rel="#L996">996</span>
<span id="L997" rel="#L997">997</span>
<span id="L998" rel="#L998">998</span>
<span id="L999" rel="#L999">999</span>
<span id="L1000" rel="#L1000">1000</span>
<span id="L1001" rel="#L1001">1001</span>
<span id="L1002" rel="#L1002">1002</span>
<span id="L1003" rel="#L1003">1003</span>
<span id="L1004" rel="#L1004">1004</span>
</pre>
          </td>
          <td width="100%">
                  <div class="highlight"><pre><div class='line' id='LC1'><span class="cm">/*</span></div><div class='line' id='LC2'><span class="cm"> Servo8Bit.cpp - Interrupt driven Servo library for the Attiny45 and Attiny85 that uses an 8 bit timer.</span></div><div class='line' id='LC3'><span class="cm"> Version 0.6</span></div><div class='line' id='LC4'><span class="cm"> Copyright (c) 2011 Ilya Brutman.  All right reserved.</span></div><div class='line' id='LC5'><br/></div><div class='line' id='LC6'><span class="cm"> This library is free software; you can redistribute it and/or</span></div><div class='line' id='LC7'><span class="cm"> modify it under the terms of the GNU Lesser General Public</span></div><div class='line' id='LC8'><span class="cm"> License as published by the Free Software Foundation; either</span></div><div class='line' id='LC9'><span class="cm"> version 2.1 of the License, or (at your option) any later version.</span></div><div class='line' id='LC10'><br/></div><div class='line' id='LC11'><span class="cm"> This library is distributed in the hope that it will be useful,</span></div><div class='line' id='LC12'><span class="cm"> but WITHOUT ANY WARRANTY; without even the implied warranty of</span></div><div class='line' id='LC13'><span class="cm"> MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU</span></div><div class='line' id='LC14'><span class="cm"> Lesser General Public License for more details.</span></div><div class='line' id='LC15'><br/></div><div class='line' id='LC16'><span class="cm"> You should have received a copy of the GNU Lesser General Public</span></div><div class='line' id='LC17'><span class="cm"> License along with this library; if not, write to the Free Software</span></div><div class='line' id='LC18'><span class="cm"> Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA</span></div><div class='line' id='LC19'><span class="cm"> */</span></div><div class='line' id='LC20'><br/></div><div class='line' id='LC21'><br/></div><div class='line' id='LC22'><span class="cm">/*</span></div><div class='line' id='LC23'><br/></div><div class='line' id='LC24'><span class="cm">  A servo is activated by creating an instance of the Servo8Bit class passing the desired pin to the attach() method.</span></div><div class='line' id='LC25'><span class="cm">  The servos are pulsed in the background using the value most recently written using the write() method</span></div><div class='line' id='LC26'><br/></div><div class='line' id='LC27'><br/></div><div class='line' id='LC28'><span class="cm">  The methods are:</span></div><div class='line' id='LC29'><br/></div><div class='line' id='LC30'><span class="cm">   Servo8Bit - Class for manipulating servo motors connected to Attiny pins.</span></div><div class='line' id='LC31'><br/></div><div class='line' id='LC32'><span class="cm">   attach(pin)           - Attaches a servo motor to an i/o pin.</span></div><div class='line' id='LC33'><span class="cm">   attach(pin, min, max) - Attaches to a pin setting min and max values in microseconds</span></div><div class='line' id='LC34'><span class="cm">                           default min is 544, max is 2400</span></div><div class='line' id='LC35'><br/></div><div class='line' id='LC36'><span class="cm">   write()               - Sets the servo angle in degrees.  (invalid angle that is valid as pulse in microseconds is treated as microseconds)</span></div><div class='line' id='LC37'><span class="cm">   writeMicroseconds()   - Sets the servo pulse width in microseconds</span></div><div class='line' id='LC38'><span class="cm">   read()                - Gets the last written servo pulse width as an angle between 0 and 180.</span></div><div class='line' id='LC39'><span class="cm">   readMicroseconds()    - Gets the last written servo pulse width in microseconds.</span></div><div class='line' id='LC40'><span class="cm">   attached()            - Returns true if there is a servo attached.</span></div><div class='line' id='LC41'><span class="cm">   detach()              - Stops an attached servos from pulsing its i/o pin.</span></div><div class='line' id='LC42'><span class="cm"> */</span></div><div class='line' id='LC43'><br/></div><div class='line' id='LC44'><br/></div><div class='line' id='LC45'><span class="c1">//TODO: Add an explaination of how this driver works. Include plenty of ASCII diagrams.</span></div><div class='line' id='LC46'><br/></div><div class='line' id='LC47'><span class="cp">#include &quot;Servo8Bit.h&quot;</span></div><div class='line' id='LC48'><span class="cp">#include &lt;inttypes.h&gt;</span></div><div class='line' id='LC49'><span class="cp">#include &lt;avr/io.h&gt;</span></div><div class='line' id='LC50'><span class="cp">#include &lt;avr/interrupt.h&gt;</span></div><div class='line' id='LC51'><br/></div><div class='line' id='LC52'><span class="c1">//There two things defined in this file</span></div><div class='line' id='LC53'><span class="c1">// *The Servo Sequencer - which is the actual driver that generates pulses</span></div><div class='line' id='LC54'><span class="c1">// *The Servo class - which provides the Arduino-like interface</span></div><div class='line' id='LC55'><br/></div><div class='line' id='LC56'><br/></div><div class='line' id='LC57'><br/></div><div class='line' id='LC58'><span class="cp">#ifdef USE_TIMER0</span></div><div class='line' id='LC59'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="err">#</span><span class="n">define</span> <span class="n">TCNTn</span>   <span class="n">TCNT0</span></div><div class='line' id='LC60'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="err">#</span><span class="n">define</span> <span class="n">OCRnx</span>   <span class="n">OCR0A</span></div><div class='line' id='LC61'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="err">#</span><span class="n">define</span> <span class="n">OCFnx</span>   <span class="n">OCF0A</span></div><div class='line' id='LC62'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="err">#</span><span class="n">define</span> <span class="n">OCIEnx</span>  <span class="n">OCIE0A</span></div><div class='line' id='LC63'><span class="cp">#endif</span></div><div class='line' id='LC64'><br/></div><div class='line' id='LC65'><span class="cp">#ifdef USE_TIMER1</span></div><div class='line' id='LC66'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="err">#</span><span class="n">define</span> <span class="n">TCNTn</span>   <span class="n">TCNT1</span></div><div class='line' id='LC67'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="err">#</span><span class="n">define</span> <span class="n">OCRnx</span>   <span class="n">OCR1A</span></div><div class='line' id='LC68'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="err">#</span><span class="n">define</span> <span class="n">OCFnx</span>   <span class="n">OCF1A</span></div><div class='line' id='LC69'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="err">#</span><span class="n">define</span> <span class="n">OCIEnx</span>  <span class="n">OCIE1A</span></div><div class='line' id='LC70'><span class="cp">#endif</span></div><div class='line' id='LC71'><br/></div><div class='line' id='LC72'><span class="c1">// Trim Duration is about the total combined time spent inside the Compare Match ISR</span></div><div class='line' id='LC73'><span class="c1">// This time is in timer ticks, where each tick is always 8 microseconds.</span></div><div class='line' id='LC74'><span class="cp">#define TRIM_DURATION 4</span></div><div class='line' id='LC75'><br/></div><div class='line' id='LC76'><br/></div><div class='line' id='LC77'><span class="c1">//This is the driver class responsible for generating the servo control pulses</span></div><div class='line' id='LC78'><span class="c1">// This class is purely static.</span></div><div class='line' id='LC79'><span class="k">class</span> <span class="nc">ServoSequencer</span></div><div class='line' id='LC80'><span class="p">{</span></div><div class='line' id='LC81'><span class="nl">public:</span></div><div class='line' id='LC82'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//=============================================================================</span></div><div class='line' id='LC83'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">// Servo Sequencer public functions</span></div><div class='line' id='LC84'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//=============================================================================</span></div><div class='line' id='LC85'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">static</span> <span class="kt">uint8_t</span>  <span class="n">registerServo</span><span class="p">();</span></div><div class='line' id='LC86'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//              Reserves a slot for a servo in the pulse sequence</span></div><div class='line' id='LC87'><br/></div><div class='line' id='LC88'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">static</span> <span class="kt">void</span>     <span class="nf">deregisterServo</span><span class="p">(</span><span class="kt">uint8_t</span> <span class="n">servoSlotNumber</span><span class="p">);</span></div><div class='line' id='LC89'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//              Frees an occupied slot</span></div><div class='line' id='LC90'><br/></div><div class='line' id='LC91'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">static</span> <span class="kt">void</span>     <span class="nf">setServoPulseLength</span><span class="p">(</span><span class="kt">uint8_t</span> <span class="n">servoNumber</span><span class="p">,</span> <span class="kt">uint16_t</span> <span class="n">newLengthInMicroseconds</span><span class="p">);</span></div><div class='line' id='LC92'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//              Updates the pulse length of a servo to a new value</span></div><div class='line' id='LC93'><br/></div><div class='line' id='LC94'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">static</span> <span class="kt">uint16_t</span> <span class="nf">getServoPulseLength</span><span class="p">(</span><span class="kt">uint8_t</span> <span class="n">servoNumber</span><span class="p">);</span></div><div class='line' id='LC95'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//              returns the pulse length of a servo in microseconds</span></div><div class='line' id='LC96'><br/></div><div class='line' id='LC97'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">static</span> <span class="kt">void</span>     <span class="nf">setServoPin</span><span class="p">(</span><span class="kt">uint8_t</span> <span class="n">servoNumber</span><span class="p">,</span> <span class="kt">uint8_t</span> <span class="n">newPin</span><span class="p">);</span></div><div class='line' id='LC98'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//              Updates the pin that will be pulsed</span></div><div class='line' id='LC99'><br/></div><div class='line' id='LC100'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">static</span> <span class="kt">void</span>     <span class="nf">enableDisableServo</span><span class="p">(</span><span class="kt">uint8_t</span> <span class="n">servoNumber</span><span class="p">,</span> <span class="kt">bool</span> <span class="n">servoShouldBeEnabled</span><span class="p">);</span></div><div class='line' id='LC101'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//              Enable or disable a servo in a slot. A pulse is not generated for a servo slot that is disabled.</span></div><div class='line' id='LC102'><br/></div><div class='line' id='LC103'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">static</span> <span class="kt">bool</span>     <span class="nf">isEnabled</span><span class="p">(</span><span class="kt">uint8_t</span> <span class="n">servoNumber</span><span class="p">);</span></div><div class='line' id='LC104'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//              returns true is the servo is enabled</span></div><div class='line' id='LC105'><br/></div><div class='line' id='LC106'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="kr">inline</span> <span class="k">static</span> <span class="kt">void</span> <span class="nf">timerCompareMatchISR</span><span class="p">();</span></div><div class='line' id='LC107'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//              Handles a timer compare match.</span></div><div class='line' id='LC108'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//              Should only be called when the timer compare match interrupt fires.</span></div><div class='line' id='LC109'><br/></div><div class='line' id='LC110'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//=============================================================================</span></div><div class='line' id='LC111'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">// Servo Sequencer public constants</span></div><div class='line' id='LC112'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//=============================================================================</span></div><div class='line' id='LC113'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">static</span> <span class="k">const</span> <span class="kt">uint8_t</span> <span class="n">kInvalidServoIndex</span> <span class="o">=</span> <span class="mh">0xFF</span><span class="p">;</span></div><div class='line' id='LC114'><br/></div><div class='line' id='LC115'><br/></div><div class='line' id='LC116'><br/></div><div class='line' id='LC117'><span class="nl">private:</span></div><div class='line' id='LC118'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//=============================================================================</span></div><div class='line' id='LC119'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">// Servo Sequencer types</span></div><div class='line' id='LC120'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//=============================================================================</span></div><div class='line' id='LC121'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//This enum defines the states of the Servo Sequencer</span></div><div class='line' id='LC122'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">enum</span> <span class="n">SequencerState_t</span></div><div class='line' id='LC123'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="p">{</span></div><div class='line' id='LC124'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">WAITING_FOR_512_MARK</span><span class="p">,</span></div><div class='line' id='LC125'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">WAITING_TO_SET_PIN_LOW</span><span class="p">,</span></div><div class='line' id='LC126'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">WAITING_FOR_2048_MARK</span><span class="p">,</span></div><div class='line' id='LC127'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">WAITING_TO_SET_PIN_HIGH</span></div><div class='line' id='LC128'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="p">};</span></div><div class='line' id='LC129'><br/></div><div class='line' id='LC130'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//This struct defines a single servo slot</span></div><div class='line' id='LC131'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">struct</span> <span class="n">ServoEntry</span></div><div class='line' id='LC132'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="p">{</span></div><div class='line' id='LC133'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="kt">uint8_t</span>  <span class="n">pulseLengthInTicks</span><span class="p">;</span>    <span class="c1">//length of pulse in ticks after offset is applied</span></div><div class='line' id='LC134'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="kt">uint8_t</span>  <span class="n">pin</span><span class="p">;</span>                   <span class="c1">//which pin to pulse on portB</span></div><div class='line' id='LC135'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="kt">bool</span>     <span class="n">enabled</span><span class="p">;</span>               <span class="c1">//True when this servo should be pulsed</span></div><div class='line' id='LC136'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="kt">bool</span>     <span class="n">slotOccupied</span><span class="p">;</span>          <span class="c1">//True when this servo entry is allocated to a servo</span></div><div class='line' id='LC137'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="p">};</span></div><div class='line' id='LC138'><br/></div><div class='line' id='LC139'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//=============================================================================</span></div><div class='line' id='LC140'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">// Servo Sequencer private variables</span></div><div class='line' id='LC141'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//=============================================================================</span></div><div class='line' id='LC142'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">static</span> <span class="k">const</span>    <span class="kt">uint16_t</span>          <span class="n">kMaxNumberOfServosSupported</span> <span class="o">=</span> <span class="mi">5</span><span class="p">;</span>  <span class="c1">//The number of servos to support. See NOTE1 below.</span></div><div class='line' id='LC143'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">static</span> <span class="k">volatile</span> <span class="n">SequencerState_t</span>  <span class="n">state</span><span class="p">;</span>                            <span class="c1">//The current state of the driver</span></div><div class='line' id='LC144'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">static</span>          <span class="kt">bool</span>              <span class="n">timerIsSetup</span><span class="p">;</span>                     <span class="c1">//True if the timer used by this driver was configured</span></div><div class='line' id='LC145'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">static</span>          <span class="kt">bool</span>              <span class="n">servoArrayIsInited</span><span class="p">;</span>               <span class="c1">//True if the servo Registry array was initialized with default values.</span></div><div class='line' id='LC146'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">static</span>          <span class="n">ServoEntry</span>        <span class="n">servoRegistry</span><span class="p">[</span><span class="n">kMaxNumberOfServosSupported</span><span class="p">];</span> <span class="c1">//The array of servo slots</span></div><div class='line' id='LC147'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">static</span> <span class="k">volatile</span> <span class="kt">uint8_t</span>           <span class="n">servoIndex</span><span class="p">;</span>                       <span class="c1">//The index of the current servo slot we are working with.</span></div><div class='line' id='LC148'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//With 5 servos, we go through the whole servoRegistry every 20 milliseconds exactly.</span></div><div class='line' id='LC149'><br/></div><div class='line' id='LC150'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//=============================================================================</span></div><div class='line' id='LC151'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">// Servo Sequencer private functions</span></div><div class='line' id='LC152'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//=============================================================================</span></div><div class='line' id='LC153'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//This is a purely static class. Disallow making instances of this class.</span></div><div class='line' id='LC154'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">ServoSequencer</span><span class="p">();</span>              <span class="c1">//private constructor</span></div><div class='line' id='LC155'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">static</span> <span class="kt">void</span> <span class="nf">servoTimerSetup</span><span class="p">();</span> <span class="c1">//Configures the timer used by this driver</span></div><div class='line' id='LC156'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">static</span> <span class="kt">void</span> <span class="nf">setupTimerPrescaler</span><span class="p">();</span> <span class="c1">//helper function to setup the prescaler</span></div><div class='line' id='LC157'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">static</span> <span class="kt">void</span> <span class="nf">initServoArray</span><span class="p">();</span>  <span class="c1">//sets default values to each element of the servoRegistry array</span></div><div class='line' id='LC158'><br/></div><div class='line' id='LC159'><span class="p">};</span><span class="c1">//end ServoSequencer</span></div><div class='line' id='LC160'><br/></div><div class='line' id='LC161'><br/></div><div class='line' id='LC162'><br/></div><div class='line' id='LC163'><span class="c1">//=============================================================================</span></div><div class='line' id='LC164'><span class="c1">// Servo Sequencer static variables initialization</span></div><div class='line' id='LC165'><span class="c1">//=============================================================================</span></div><div class='line' id='LC166'><span class="k">volatile</span> <span class="n">ServoSequencer</span><span class="o">::</span><span class="n">SequencerState_t</span> <span class="n">ServoSequencer</span><span class="o">::</span><span class="n">state</span>         <span class="o">=</span> <span class="n">ServoSequencer</span><span class="o">::</span><span class="n">WAITING_TO_SET_PIN_HIGH</span><span class="p">;</span></div><div class='line' id='LC167'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="kt">bool</span>                             <span class="n">ServoSequencer</span><span class="o">::</span><span class="n">timerIsSetup</span>  <span class="o">=</span> <span class="nb">false</span><span class="p">;</span></div><div class='line' id='LC168'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="kt">bool</span>                             <span class="n">ServoSequencer</span><span class="o">::</span><span class="n">servoArrayIsInited</span> <span class="o">=</span> <span class="nb">false</span><span class="p">;</span></div><div class='line' id='LC169'><span class="k">volatile</span> <span class="kt">uint8_t</span>                          <span class="n">ServoSequencer</span><span class="o">::</span><span class="n">servoIndex</span>    <span class="o">=</span> <span class="mi">0</span><span class="p">;</span></div><div class='line' id='LC170'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">ServoSequencer</span><span class="o">::</span><span class="n">ServoEntry</span>       <span class="n">ServoSequencer</span><span class="o">::</span><span class="n">servoRegistry</span><span class="p">[</span><span class="n">kMaxNumberOfServosSupported</span><span class="p">];</span></div><div class='line' id='LC171'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//TODO: Add the rest of the class variables here for better organization?</span></div><div class='line' id='LC172'><br/></div><div class='line' id='LC173'><br/></div><div class='line' id='LC174'><span class="c1">//NOTE1:</span></div><div class='line' id='LC175'><span class="c1">// With 5 servos, each servo is pulsed exactly every 20 milliseconds. You can increase this number to have</span></div><div class='line' id='LC176'><span class="c1">// the driver support more servos. The servos are pulsed in sequence and each servo takes up 4 ms of time.</span></div><div class='line' id='LC177'><span class="c1">// So if you change this number to 6 then each servo will be pulsed every 24 milliseconds.</span></div><div class='line' id='LC178'><br/></div><div class='line' id='LC179'><br/></div><div class='line' id='LC180'><br/></div><div class='line' id='LC181'><span class="c1">//=============================================================================</span></div><div class='line' id='LC182'><span class="c1">// FUNCTION:    bool registerServo()</span></div><div class='line' id='LC183'><span class="c1">//</span></div><div class='line' id='LC184'><span class="c1">// DESCRIPTION: Reserves a slot for a servo in the pulse sequence.</span></div><div class='line' id='LC185'><span class="c1">//              There is a limited number of slots.</span></div><div class='line' id='LC186'><span class="c1">//</span></div><div class='line' id='LC187'><span class="c1">// INPUT:       Nothing</span></div><div class='line' id='LC188'><span class="c1">//</span></div><div class='line' id='LC189'><span class="c1">// RETURNS:     On success returns the slot number.</span></div><div class='line' id='LC190'><span class="c1">//              If no free slot is found returns kInvalidServoIndex.</span></div><div class='line' id='LC191'><span class="c1">//=============================================================================</span></div><div class='line' id='LC192'><span class="kt">uint8_t</span> <span class="n">ServoSequencer</span><span class="o">::</span><span class="n">registerServo</span><span class="p">()</span></div><div class='line' id='LC193'><span class="p">{</span></div><div class='line' id='LC194'><br/></div><div class='line' id='LC195'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">if</span><span class="p">(</span><span class="n">servoArrayIsInited</span> <span class="o">==</span> <span class="nb">false</span><span class="p">)</span></div><div class='line' id='LC196'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="p">{</span></div><div class='line' id='LC197'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">initServoArray</span><span class="p">();</span></div><div class='line' id='LC198'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="p">}</span></div><div class='line' id='LC199'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">else</span></div><div class='line' id='LC200'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="p">{</span></div><div class='line' id='LC201'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//the servo array is already inited. Do nothing.</span></div><div class='line' id='LC202'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//It needs to be setup only once. We do it when the first servo is registered.</span></div><div class='line' id='LC203'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="p">}</span></div><div class='line' id='LC204'><br/></div><div class='line' id='LC205'><br/></div><div class='line' id='LC206'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//find a free slot in the servo registry</span></div><div class='line' id='LC207'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">for</span><span class="p">(</span><span class="kt">uint8_t</span> <span class="n">i</span> <span class="o">=</span> <span class="mi">0</span><span class="p">;</span> <span class="n">i</span> <span class="o">&lt;</span> <span class="n">kMaxNumberOfServosSupported</span><span class="p">;</span> <span class="n">i</span><span class="o">++</span><span class="p">)</span></div><div class='line' id='LC208'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="p">{</span></div><div class='line' id='LC209'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">if</span><span class="p">(</span><span class="n">servoRegistry</span><span class="p">[</span><span class="n">i</span><span class="p">].</span><span class="n">slotOccupied</span> <span class="o">==</span> <span class="nb">false</span><span class="p">)</span></div><div class='line' id='LC210'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="p">{</span></div><div class='line' id='LC211'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//found a free slot.</span></div><div class='line' id='LC212'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">servoRegistry</span><span class="p">[</span><span class="n">i</span><span class="p">].</span><span class="n">slotOccupied</span> <span class="o">=</span> <span class="nb">true</span><span class="p">;</span></div><div class='line' id='LC213'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//return the slot number</span></div><div class='line' id='LC214'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">return</span> <span class="n">i</span><span class="p">;</span></div><div class='line' id='LC215'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="p">}</span></div><div class='line' id='LC216'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">else</span></div><div class='line' id='LC217'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="p">{</span></div><div class='line' id='LC218'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//this slot is not free, check the next one.</span></div><div class='line' id='LC219'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="p">}</span></div><div class='line' id='LC220'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="p">}</span></div><div class='line' id='LC221'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//no free slots were found.</span></div><div class='line' id='LC222'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">return</span> <span class="n">kInvalidServoIndex</span><span class="p">;</span></div><div class='line' id='LC223'><span class="p">}</span><span class="c1">//end registerServo</span></div><div class='line' id='LC224'><br/></div><div class='line' id='LC225'><br/></div><div class='line' id='LC226'><span class="c1">//=============================================================================</span></div><div class='line' id='LC227'><span class="c1">// FUNCTION:    bool deregisterServo(uint8_t servoSlotNumber)</span></div><div class='line' id='LC228'><span class="c1">//</span></div><div class='line' id='LC229'><span class="c1">// DESCRIPTION: Frees up a slot in the pulse sequence.</span></div><div class='line' id='LC230'><span class="c1">//</span></div><div class='line' id='LC231'><span class="c1">// INPUT:       servoSlotNumber - The slot number to deallocate.</span></div><div class='line' id='LC232'><span class="c1">//</span></div><div class='line' id='LC233'><span class="c1">// RETURNS:     Nothing</span></div><div class='line' id='LC234'><span class="c1">//=============================================================================</span></div><div class='line' id='LC235'><span class="kt">void</span> <span class="n">ServoSequencer</span><span class="o">::</span><span class="n">deregisterServo</span><span class="p">(</span><span class="kt">uint8_t</span> <span class="n">servoSlotNumber</span><span class="p">)</span></div><div class='line' id='LC236'><span class="p">{</span></div><div class='line' id='LC237'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//make sure we got a valid slot number</span></div><div class='line' id='LC238'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">if</span><span class="p">(</span><span class="n">servoSlotNumber</span> <span class="o">&lt;</span> <span class="n">kMaxNumberOfServosSupported</span><span class="p">)</span></div><div class='line' id='LC239'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="p">{</span></div><div class='line' id='LC240'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">servoRegistry</span><span class="p">[</span><span class="n">servoSlotNumber</span><span class="p">].</span><span class="n">enabled</span>      <span class="o">=</span> <span class="nb">false</span><span class="p">;</span></div><div class='line' id='LC241'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">servoRegistry</span><span class="p">[</span><span class="n">servoSlotNumber</span><span class="p">].</span><span class="n">slotOccupied</span> <span class="o">=</span> <span class="nb">false</span><span class="p">;</span></div><div class='line' id='LC242'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="p">}</span></div><div class='line' id='LC243'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">else</span></div><div class='line' id='LC244'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="p">{</span></div><div class='line' id='LC245'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//we got a slot number that is out of range. Do nothing.</span></div><div class='line' id='LC246'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="p">}</span></div><div class='line' id='LC247'><span class="p">}</span><span class="c1">//end deregisterServo</span></div><div class='line' id='LC248'><br/></div><div class='line' id='LC249'><br/></div><div class='line' id='LC250'><br/></div><div class='line' id='LC251'><br/></div><div class='line' id='LC252'><br/></div><div class='line' id='LC253'><span class="c1">//=============================================================================</span></div><div class='line' id='LC254'><span class="c1">// FUNCTION:    void setServoPulseLength(uint8_t servoNumber, uint16_t newLengthInMicroseconds)</span></div><div class='line' id='LC255'><span class="c1">//</span></div><div class='line' id='LC256'><span class="c1">// DESCRIPTION: Updates a servo slots with a new pulse length.</span></div><div class='line' id='LC257'><span class="c1">//              Only works on allocated slots.</span></div><div class='line' id='LC258'><span class="c1">//</span></div><div class='line' id='LC259'><span class="c1">// INPUT:       servoNumber - the slot number to update</span></div><div class='line' id='LC260'><span class="c1">//              newLengthInMicroseconds - the new pulse length to set</span></div><div class='line' id='LC261'><span class="c1">//</span></div><div class='line' id='LC262'><span class="c1">// RETURNS:     Nothing</span></div><div class='line' id='LC263'><span class="c1">//=============================================================================</span></div><div class='line' id='LC264'><span class="kt">void</span> <span class="n">ServoSequencer</span><span class="o">::</span><span class="n">setServoPulseLength</span><span class="p">(</span><span class="kt">uint8_t</span> <span class="n">servoNumber</span><span class="p">,</span> <span class="kt">uint16_t</span> <span class="n">newLengthInMicroseconds</span><span class="p">)</span></div><div class='line' id='LC265'><span class="p">{</span></div><div class='line' id='LC266'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//make sure we got a valid slot number and the slot is registered to a servo</span></div><div class='line' id='LC267'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">if</span><span class="p">(</span> <span class="p">(</span><span class="n">servoNumber</span> <span class="o">&lt;</span> <span class="n">kMaxNumberOfServosSupported</span>      <span class="p">)</span> <span class="o">&amp;&amp;</span></div><div class='line' id='LC268'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="p">(</span><span class="n">servoRegistry</span><span class="p">[</span><span class="n">servoNumber</span><span class="p">].</span><span class="n">slotOccupied</span> <span class="o">==</span> <span class="nb">true</span><span class="p">)</span>   <span class="p">)</span></div><div class='line' id='LC269'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="p">{</span></div><div class='line' id='LC270'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//Convert the servo pulse length into timer ticks.</span></div><div class='line' id='LC271'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//Each timer tick is 8 microseconds.</span></div><div class='line' id='LC272'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="kt">int16_t</span> <span class="n">newLengthInClockTicks</span> <span class="o">=</span> <span class="n">newLengthInMicroseconds</span> <span class="o">/</span> <span class="mi">8</span><span class="p">;</span></div><div class='line' id='LC273'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//subtract the pulse offset</span></div><div class='line' id='LC274'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">newLengthInClockTicks</span> <span class="o">-=</span> <span class="mi">64</span><span class="p">;</span></div><div class='line' id='LC275'><br/></div><div class='line' id='LC276'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//make sure the length of this pulse is within the acceptable range</span></div><div class='line' id='LC277'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">if</span><span class="p">(</span> <span class="p">(</span><span class="n">newLengthInClockTicks</span> <span class="o">&gt;</span> <span class="o">-</span><span class="mi">1</span><span class="p">)</span> <span class="o">&amp;&amp;</span> <span class="p">(</span><span class="n">newLengthInClockTicks</span> <span class="o">&lt;</span> <span class="mi">256</span><span class="p">)</span> <span class="p">)</span></div><div class='line' id='LC278'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="p">{</span></div><div class='line' id='LC279'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">servoRegistry</span><span class="p">[</span><span class="n">servoNumber</span><span class="p">].</span><span class="n">pulseLengthInTicks</span> <span class="o">=</span> <span class="k">static_cast</span><span class="o">&lt;</span><span class="kt">uint8_t</span><span class="o">&gt;</span><span class="p">(</span><span class="n">newLengthInClockTicks</span><span class="p">);</span></div><div class='line' id='LC280'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//Programing note: If pulseLengthInTicks is ever changed to be larger than 1 byte in size then</span></div><div class='line' id='LC281'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//                 interrupts would need to be disabled when updating it to a new value.</span></div><div class='line' id='LC282'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="p">}</span></div><div class='line' id='LC283'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">else</span></div><div class='line' id='LC284'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="p">{</span></div><div class='line' id='LC285'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//The new pulse length is too short or long than what we can generate</span></div><div class='line' id='LC286'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="p">}</span></div><div class='line' id='LC287'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="p">}</span></div><div class='line' id='LC288'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">else</span></div><div class='line' id='LC289'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="p">{</span></div><div class='line' id='LC290'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//Servo number is out of range or is not allocate to a servo. Do nothing.</span></div><div class='line' id='LC291'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="p">}</span></div><div class='line' id='LC292'><span class="p">}</span><span class="c1">//end setServoPulseLength</span></div><div class='line' id='LC293'><br/></div><div class='line' id='LC294'><br/></div><div class='line' id='LC295'><br/></div><div class='line' id='LC296'><span class="c1">//=============================================================================</span></div><div class='line' id='LC297'><span class="c1">// FUNCTION:    void getServoPulseLength(uint8_t servoNumber)</span></div><div class='line' id='LC298'><span class="c1">//</span></div><div class='line' id='LC299'><span class="c1">// DESCRIPTION: Gets the pulse length of a servo slot.</span></div><div class='line' id='LC300'><span class="c1">//              Only works on allocated slots.</span></div><div class='line' id='LC301'><span class="c1">//</span></div><div class='line' id='LC302'><span class="c1">// INPUT:       servoNumber - which slot to get the pulse length from</span></div><div class='line' id='LC303'><span class="c1">//</span></div><div class='line' id='LC304'><span class="c1">// RETURNS:     The pulse length in microseconds</span></div><div class='line' id='LC305'><span class="c1">//=============================================================================</span></div><div class='line' id='LC306'><span class="kt">uint16_t</span> <span class="n">ServoSequencer</span><span class="o">::</span><span class="n">getServoPulseLength</span><span class="p">(</span><span class="kt">uint8_t</span> <span class="n">servoNumber</span><span class="p">)</span></div><div class='line' id='LC307'><span class="p">{</span></div><div class='line' id='LC308'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="kt">uint16_t</span> <span class="n">pulseLength</span> <span class="o">=</span> <span class="mi">0</span><span class="p">;</span></div><div class='line' id='LC309'><br/></div><div class='line' id='LC310'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//make sure we got a valid slot number and the slot is registered to a servo</span></div><div class='line' id='LC311'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">if</span><span class="p">(</span> <span class="p">(</span><span class="n">servoNumber</span> <span class="o">&lt;</span> <span class="n">kMaxNumberOfServosSupported</span>      <span class="p">)</span> <span class="o">&amp;&amp;</span></div><div class='line' id='LC312'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="p">(</span><span class="n">servoRegistry</span><span class="p">[</span><span class="n">servoNumber</span><span class="p">].</span><span class="n">slotOccupied</span> <span class="o">==</span> <span class="nb">true</span><span class="p">)</span>   <span class="p">)</span></div><div class='line' id='LC313'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="p">{</span></div><div class='line' id='LC314'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">pulseLength</span> <span class="o">=</span> <span class="p">(</span><span class="n">servoRegistry</span><span class="p">[</span><span class="n">servoNumber</span><span class="p">].</span><span class="n">pulseLengthInTicks</span> <span class="o">*</span> <span class="mi">8</span><span class="p">)</span> <span class="o">+</span> <span class="mi">64</span><span class="p">;</span></div><div class='line' id='LC315'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="p">}</span></div><div class='line' id='LC316'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">else</span></div><div class='line' id='LC317'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="p">{</span></div><div class='line' id='LC318'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//Servo number is out of range or is not allocate to a servo. Do nothing.</span></div><div class='line' id='LC319'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="p">}</span></div><div class='line' id='LC320'><br/></div><div class='line' id='LC321'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">return</span> <span class="n">pulseLength</span><span class="p">;</span></div><div class='line' id='LC322'><span class="p">}</span><span class="c1">//end getServoPulseLength</span></div><div class='line' id='LC323'><br/></div><div class='line' id='LC324'><br/></div><div class='line' id='LC325'><span class="c1">//=============================================================================</span></div><div class='line' id='LC326'><span class="c1">// FUNCTION:    void setServoPin(uint8_t servoNumber, uint8_t newPin)</span></div><div class='line' id='LC327'><span class="c1">//</span></div><div class='line' id='LC328'><span class="c1">// DESCRIPTION: Sets which pin on PortB should be pulsed for a servo slot.</span></div><div class='line' id='LC329'><span class="c1">//</span></div><div class='line' id='LC330'><span class="c1">// INPUT:       servoNumber - which servo slot to update</span></div><div class='line' id='LC331'><span class="c1">//              newPin - which pin on portB should be pulsed</span></div><div class='line' id='LC332'><span class="c1">//</span></div><div class='line' id='LC333'><span class="c1">// RETURNS:     Nothing</span></div><div class='line' id='LC334'><span class="c1">//</span></div><div class='line' id='LC335'><span class="c1">//=============================================================================</span></div><div class='line' id='LC336'><span class="kt">void</span> <span class="n">ServoSequencer</span><span class="o">::</span><span class="n">setServoPin</span><span class="p">(</span><span class="kt">uint8_t</span> <span class="n">servoNumber</span><span class="p">,</span> <span class="kt">uint8_t</span> <span class="n">newPin</span><span class="p">)</span></div><div class='line' id='LC337'><span class="p">{</span></div><div class='line' id='LC338'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//make sure we got a valid slot number and the slot is registered to a servo</span></div><div class='line' id='LC339'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">if</span><span class="p">(</span> <span class="p">(</span><span class="n">servoNumber</span> <span class="o">&lt;</span> <span class="n">kMaxNumberOfServosSupported</span>      <span class="p">)</span> <span class="o">&amp;&amp;</span></div><div class='line' id='LC340'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="p">(</span><span class="n">servoRegistry</span><span class="p">[</span><span class="n">servoNumber</span><span class="p">].</span><span class="n">slotOccupied</span> <span class="o">==</span> <span class="nb">true</span><span class="p">)</span>   <span class="p">)</span></div><div class='line' id='LC341'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="p">{</span></div><div class='line' id='LC342'><br/></div><div class='line' id='LC343'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">servoRegistry</span><span class="p">[</span><span class="n">servoNumber</span><span class="p">].</span><span class="n">pin</span> <span class="o">=</span> <span class="n">newPin</span><span class="p">;</span></div><div class='line' id='LC344'><br/></div><div class='line' id='LC345'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="p">}</span></div><div class='line' id='LC346'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">else</span></div><div class='line' id='LC347'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="p">{</span></div><div class='line' id='LC348'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//Servo number is out of range or is not allocate to a servo. Do nothing.</span></div><div class='line' id='LC349'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="p">}</span></div><div class='line' id='LC350'><span class="p">}</span><span class="c1">//end setServoPin</span></div><div class='line' id='LC351'><br/></div><div class='line' id='LC352'><br/></div><div class='line' id='LC353'><span class="c1">//=============================================================================</span></div><div class='line' id='LC354'><span class="c1">// FUNCTION:    void enableDisableServo(uint8_t servoNumber, bool servoShouldBeEnabled)</span></div><div class='line' id='LC355'><span class="c1">//</span></div><div class='line' id='LC356'><span class="c1">// DESCRIPTION: Enabled or disables an allocated servo slot.</span></div><div class='line' id='LC357'><span class="c1">//              An enabled slot generates a pwm wave on its pin.</span></div><div class='line' id='LC358'><span class="c1">//              A disabled slot does not.</span></div><div class='line' id='LC359'><span class="c1">//</span></div><div class='line' id='LC360'><span class="c1">// INPUT:       servoNumber - which servo slot to update</span></div><div class='line' id='LC361'><span class="c1">//              servoShouldBeEnabled - true to enable the servo slot</span></div><div class='line' id='LC362'><span class="c1">//                                     false to disable the servo slot</span></div><div class='line' id='LC363'><span class="c1">//</span></div><div class='line' id='LC364'><span class="c1">// RETURNS:     Nothing</span></div><div class='line' id='LC365'><span class="c1">//</span></div><div class='line' id='LC366'><span class="c1">//=============================================================================</span></div><div class='line' id='LC367'><span class="kt">void</span> <span class="n">ServoSequencer</span><span class="o">::</span><span class="n">enableDisableServo</span><span class="p">(</span><span class="kt">uint8_t</span> <span class="n">servoNumber</span><span class="p">,</span> <span class="kt">bool</span> <span class="n">servoShouldBeEnabled</span><span class="p">)</span></div><div class='line' id='LC368'><span class="p">{</span></div><div class='line' id='LC369'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//make sure we got a valid slot number and the slot is registered to a servo</span></div><div class='line' id='LC370'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">if</span><span class="p">(</span> <span class="p">(</span><span class="n">servoNumber</span> <span class="o">&lt;</span> <span class="n">kMaxNumberOfServosSupported</span>      <span class="p">)</span> <span class="o">&amp;&amp;</span></div><div class='line' id='LC371'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="p">(</span><span class="n">servoRegistry</span><span class="p">[</span><span class="n">servoNumber</span><span class="p">].</span><span class="n">slotOccupied</span> <span class="o">==</span> <span class="nb">true</span><span class="p">)</span>   <span class="p">)</span></div><div class='line' id='LC372'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="p">{</span></div><div class='line' id='LC373'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">if</span><span class="p">(</span><span class="n">servoShouldBeEnabled</span> <span class="o">==</span> <span class="nb">true</span><span class="p">)</span></div><div class='line' id='LC374'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="p">{</span></div><div class='line' id='LC375'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//if this is the very first servo we are enabling then configure the servo timer</span></div><div class='line' id='LC376'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">if</span><span class="p">(</span> <span class="n">timerIsSetup</span> <span class="o">==</span> <span class="nb">false</span><span class="p">)</span></div><div class='line' id='LC377'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="p">{</span></div><div class='line' id='LC378'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">servoTimerSetup</span><span class="p">();</span></div><div class='line' id='LC379'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">timerIsSetup</span> <span class="o">=</span> <span class="nb">true</span><span class="p">;</span></div><div class='line' id='LC380'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="p">}</span></div><div class='line' id='LC381'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">else</span></div><div class='line' id='LC382'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="p">{</span></div><div class='line' id='LC383'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//The timer is already setup. Do nothing.</span></div><div class='line' id='LC384'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//It needs to be setup only once. We do it when the first servo is enabled.</span></div><div class='line' id='LC385'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//We setup the timer as late as possible. This allows this servo library</span></div><div class='line' id='LC386'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//to be more compatible with various frameworks written for the attiny45/85,</span></div><div class='line' id='LC387'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//which typically configure all the timers to their liking on start up.</span></div><div class='line' id='LC388'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//Configuring our timer late allows us to overwrite these settings.</span></div><div class='line' id='LC389'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="p">}</span></div><div class='line' id='LC390'><br/></div><div class='line' id='LC391'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//enable the servo. Its pulse will now be outputed on its pin.</span></div><div class='line' id='LC392'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">servoRegistry</span><span class="p">[</span><span class="n">servoNumber</span><span class="p">].</span><span class="n">enabled</span> <span class="o">=</span> <span class="nb">true</span><span class="p">;</span></div><div class='line' id='LC393'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="p">}</span></div><div class='line' id='LC394'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">else</span></div><div class='line' id='LC395'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="p">{</span></div><div class='line' id='LC396'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//disable the servo. Its pulse will cease to be generated.</span></div><div class='line' id='LC397'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">servoRegistry</span><span class="p">[</span><span class="n">servoNumber</span><span class="p">].</span><span class="n">enabled</span> <span class="o">=</span> <span class="nb">false</span><span class="p">;</span></div><div class='line' id='LC398'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//TODO: set this servo pin low, if it is high.</span></div><div class='line' id='LC399'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//      Actually, ideally the pulse should finish by itself</span></div><div class='line' id='LC400'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//      forcing the pin low will generate a weird length pulse for the servo</span></div><div class='line' id='LC401'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//      Need to add some sort of &quot;disable pending&quot; status</span></div><div class='line' id='LC402'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="p">}</span></div><div class='line' id='LC403'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="p">}</span></div><div class='line' id='LC404'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">else</span></div><div class='line' id='LC405'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="p">{</span></div><div class='line' id='LC406'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//Servo number is out of range or is not allocate to a servo. Do nothing.</span></div><div class='line' id='LC407'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="p">}</span></div><div class='line' id='LC408'><span class="p">}</span><span class="c1">//end enableDisableServo</span></div><div class='line' id='LC409'><br/></div><div class='line' id='LC410'><br/></div><div class='line' id='LC411'><br/></div><div class='line' id='LC412'><span class="c1">//=============================================================================</span></div><div class='line' id='LC413'><span class="c1">// FUNCTION:    bool isEnabled(uint8_t servoNumber)</span></div><div class='line' id='LC414'><span class="c1">//</span></div><div class='line' id='LC415'><span class="c1">// DESCRIPTION: Determines if a servo slot is enabled.</span></div><div class='line' id='LC416'><span class="c1">//</span></div><div class='line' id='LC417'><span class="c1">// INPUT:       servoNumber - which servo slot to check</span></div><div class='line' id='LC418'><span class="c1">//</span></div><div class='line' id='LC419'><span class="c1">// RETURNS:     true if the slot is enabled</span></div><div class='line' id='LC420'><span class="c1">//              false if it is disabled or not allocated to a servo.</span></div><div class='line' id='LC421'><span class="c1">//</span></div><div class='line' id='LC422'><span class="c1">//=============================================================================</span></div><div class='line' id='LC423'><span class="kt">bool</span> <span class="n">ServoSequencer</span><span class="o">::</span><span class="n">isEnabled</span><span class="p">(</span><span class="kt">uint8_t</span> <span class="n">servoNumber</span><span class="p">)</span></div><div class='line' id='LC424'><span class="p">{</span></div><div class='line' id='LC425'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//make sure we got a valid slot number and the slot is registered to a servo</span></div><div class='line' id='LC426'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">if</span><span class="p">(</span> <span class="p">(</span><span class="n">servoNumber</span> <span class="o">&lt;</span> <span class="n">kMaxNumberOfServosSupported</span>      <span class="p">)</span> <span class="o">&amp;&amp;</span></div><div class='line' id='LC427'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="p">(</span><span class="n">servoRegistry</span><span class="p">[</span><span class="n">servoNumber</span><span class="p">].</span><span class="n">slotOccupied</span> <span class="o">==</span> <span class="nb">true</span><span class="p">)</span>   <span class="p">)</span></div><div class='line' id='LC428'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="p">{</span></div><div class='line' id='LC429'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">return</span> <span class="n">servoRegistry</span><span class="p">[</span><span class="n">servoNumber</span><span class="p">].</span><span class="n">enabled</span><span class="p">;</span></div><div class='line' id='LC430'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="p">}</span></div><div class='line' id='LC431'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">else</span></div><div class='line' id='LC432'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="p">{</span></div><div class='line' id='LC433'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//Servo number is out of range or is not allocate to a servo.</span></div><div class='line' id='LC434'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//So therefore it is not enabled.</span></div><div class='line' id='LC435'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">return</span> <span class="nb">false</span><span class="p">;</span></div><div class='line' id='LC436'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="p">}</span></div><div class='line' id='LC437'><span class="p">}</span><span class="c1">//end isEnabled</span></div><div class='line' id='LC438'><br/></div><div class='line' id='LC439'><br/></div><div class='line' id='LC440'><span class="c1">//=============================================================================</span></div><div class='line' id='LC441'><span class="c1">// FUNCTION:    void servoTimerSetup()</span></div><div class='line' id='LC442'><span class="c1">//</span></div><div class='line' id='LC443'><span class="c1">// DESCRIPTION: Sets up the timer used by this servo driver</span></div><div class='line' id='LC444'><span class="c1">//              No servo pulses can be generated until this function is called.</span></div><div class='line' id='LC445'><span class="c1">//</span></div><div class='line' id='LC446'><span class="c1">// INPUT:       Nothing</span></div><div class='line' id='LC447'><span class="c1">//</span></div><div class='line' id='LC448'><span class="c1">// RETURNS:     Nothing</span></div><div class='line' id='LC449'><span class="c1">//</span></div><div class='line' id='LC450'><span class="c1">//=============================================================================</span></div><div class='line' id='LC451'><span class="kt">void</span> <span class="n">ServoSequencer</span><span class="o">::</span><span class="n">servoTimerSetup</span><span class="p">()</span></div><div class='line' id='LC452'><span class="p">{</span></div><div class='line' id='LC453'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//set up the timer prescaler based on which timer was selected and our F_CPU clock</span></div><div class='line' id='LC454'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">setupTimerPrescaler</span><span class="p">();</span></div><div class='line' id='LC455'><br/></div><div class='line' id='LC456'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">// Enable Output Compare Match Interrupt</span></div><div class='line' id='LC457'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">TIMSK</span> <span class="o">|=</span> <span class="p">(</span><span class="mi">1</span> <span class="o">&lt;&lt;</span> <span class="n">OCIEnx</span><span class="p">);</span></div><div class='line' id='LC458'><br/></div><div class='line' id='LC459'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//reset the counter to 0</span></div><div class='line' id='LC460'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">TCNTn</span>  <span class="o">=</span> <span class="mi">0</span><span class="p">;</span></div><div class='line' id='LC461'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//set the compare value to any number larger than 0</span></div><div class='line' id='LC462'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">OCRnx</span> <span class="o">=</span> <span class="mi">255</span><span class="p">;</span></div><div class='line' id='LC463'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">// Enable global interrupts</span></div><div class='line' id='LC464'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">sei</span><span class="p">();</span></div><div class='line' id='LC465'><br/></div><div class='line' id='LC466'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="cm">/*</span></div><div class='line' id='LC467'><span class="cm">    TCNT0 - The Timer/Counter</span></div><div class='line' id='LC468'><span class="cm">    OCR0A and OCR0B - Output Compare Registers</span></div><div class='line' id='LC469'><span class="cm">    TIFR0 - Timer Interrupt Flag Register</span></div><div class='line' id='LC470'><span class="cm">    TIMSK - Timer Interrupt Mask Register</span></div><div class='line' id='LC471'><span class="cm">    TCCR0B Timer/Counter Control Register B</span></div><div class='line' id='LC472'><span class="cm">    */</span></div><div class='line' id='LC473'><br/></div><div class='line' id='LC474'><span class="p">}</span><span class="c1">//end servoTimerSetup</span></div><div class='line' id='LC475'><br/></div><div class='line' id='LC476'><br/></div><div class='line' id='LC477'><span class="c1">//=============================================================================</span></div><div class='line' id='LC478'><span class="c1">// FUNCTION:    void setupTimerPrescaler()</span></div><div class='line' id='LC479'><span class="c1">//</span></div><div class='line' id='LC480'><span class="c1">// DESCRIPTION: Helper function that sets up the timer prescaller based on what</span></div><div class='line' id='LC481'><span class="c1">//              timer is selected and the F_CPU frequence.</span></div><div class='line' id='LC482'><span class="c1">//</span></div><div class='line' id='LC483'><span class="c1">// INPUT:       Nothing</span></div><div class='line' id='LC484'><span class="c1">//</span></div><div class='line' id='LC485'><span class="c1">// RETURNS:     Nothing</span></div><div class='line' id='LC486'><span class="c1">//</span></div><div class='line' id='LC487'><span class="c1">//=============================================================================</span></div><div class='line' id='LC488'><span class="kt">void</span> <span class="n">ServoSequencer</span><span class="o">::</span><span class="n">setupTimerPrescaler</span><span class="p">()</span></div><div class='line' id='LC489'><span class="p">{</span></div><div class='line' id='LC490'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="err">#</span><span class="n">ifdef</span> <span class="n">USE_TIMER0</span></div><div class='line' id='LC491'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//reset the Timer Counter Control Register to its reset value</span></div><div class='line' id='LC492'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">TCCR0B</span> <span class="o">=</span> <span class="mi">0</span><span class="p">;</span></div><div class='line' id='LC493'><br/></div><div class='line' id='LC494'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="err">#</span><span class="k">if</span> <span class="n">F_CPU</span> <span class="o">==</span> <span class="mi">8000000L</span></div><div class='line' id='LC495'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//set counter0 prescaler to 64</span></div><div class='line' id='LC496'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//our FCLK is 8mhz so this makes each timer tick be 8 microseconds long</span></div><div class='line' id='LC497'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">TCCR0B</span> <span class="o">&amp;=</span> <span class="o">~</span><span class="p">(</span><span class="mi">1</span><span class="o">&lt;&lt;</span> <span class="n">CS02</span><span class="p">);</span> <span class="c1">//clear</span></div><div class='line' id='LC498'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">TCCR0B</span> <span class="o">|=</span>  <span class="p">(</span><span class="mi">1</span><span class="o">&lt;&lt;</span> <span class="n">CS01</span><span class="p">);</span> <span class="c1">//set</span></div><div class='line' id='LC499'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">TCCR0B</span> <span class="o">|=</span>  <span class="p">(</span><span class="mi">1</span><span class="o">&lt;&lt;</span> <span class="n">CS00</span><span class="p">);</span> <span class="c1">//set</span></div><div class='line' id='LC500'><br/></div><div class='line' id='LC501'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="err">#</span><span class="n">elif</span> <span class="n">F_CPU</span> <span class="o">==</span> <span class="mi">1000000L</span></div><div class='line' id='LC502'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//set counter0 prescaler to 8</span></div><div class='line' id='LC503'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//our F_CPU is 1mhz so this makes each timer tick be 8 microseconds long</span></div><div class='line' id='LC504'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">TCCR0B</span> <span class="o">&amp;=</span> <span class="o">~</span><span class="p">(</span><span class="mi">1</span><span class="o">&lt;&lt;</span> <span class="n">CS02</span><span class="p">);</span> <span class="c1">//clear</span></div><div class='line' id='LC505'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">TCCR0B</span> <span class="o">|=</span>  <span class="p">(</span><span class="mi">1</span><span class="o">&lt;&lt;</span> <span class="n">CS01</span><span class="p">);</span> <span class="c1">//set</span></div><div class='line' id='LC506'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">TCCR0B</span> <span class="o">&amp;=</span> <span class="o">~</span><span class="p">(</span><span class="mi">1</span><span class="o">&lt;&lt;</span> <span class="n">CS00</span><span class="p">);</span> <span class="c1">//clear</span></div><div class='line' id='LC507'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="err">#</span><span class="k">else</span></div><div class='line' id='LC508'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//unsupported clock speed</span></div><div class='line' id='LC509'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//TODO: find a way to have the compiler stop compiling and bark at the user</span></div><div class='line' id='LC510'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="err">#</span><span class="n">endif</span></div><div class='line' id='LC511'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="err">#</span><span class="n">endif</span></div><div class='line' id='LC512'><br/></div><div class='line' id='LC513'><br/></div><div class='line' id='LC514'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="err">#</span><span class="n">ifdef</span> <span class="n">USE_TIMER1</span></div><div class='line' id='LC515'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//reset the Timer Counter Control Register to its reset value</span></div><div class='line' id='LC516'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">TCCR1</span> <span class="o">=</span> <span class="mi">0</span><span class="p">;</span></div><div class='line' id='LC517'><br/></div><div class='line' id='LC518'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="err">#</span><span class="k">if</span> <span class="n">F_CPU</span> <span class="o">==</span> <span class="mi">8000000L</span></div><div class='line' id='LC519'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//set counter1 prescaler to 64</span></div><div class='line' id='LC520'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//our F_CPU is 8mhz so this makes each timer tick be 8 microseconds long</span></div><div class='line' id='LC521'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">TCCR1</span> <span class="o">&amp;=</span> <span class="o">~</span><span class="p">(</span><span class="mi">1</span><span class="o">&lt;&lt;</span> <span class="n">CS13</span><span class="p">);</span> <span class="c1">//clear</span></div><div class='line' id='LC522'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">TCCR1</span> <span class="o">|=</span>  <span class="p">(</span><span class="mi">1</span><span class="o">&lt;&lt;</span> <span class="n">CS12</span><span class="p">);</span> <span class="c1">//set</span></div><div class='line' id='LC523'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">TCCR1</span> <span class="o">|=</span>  <span class="p">(</span><span class="mi">1</span><span class="o">&lt;&lt;</span> <span class="n">CS11</span><span class="p">);</span> <span class="c1">//set</span></div><div class='line' id='LC524'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">TCCR1</span> <span class="o">|=</span>  <span class="p">(</span><span class="mi">1</span><span class="o">&lt;&lt;</span> <span class="n">CS10</span><span class="p">);</span> <span class="c1">//set</span></div><div class='line' id='LC525'><br/></div><div class='line' id='LC526'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="err">#</span><span class="n">elif</span> <span class="n">F_CPU</span> <span class="o">==</span> <span class="mi">1000000L</span></div><div class='line' id='LC527'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//set counter1 prescaler to 8</span></div><div class='line' id='LC528'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//our F_CPU is 1mhz so this makes each timer tick be 8 microseconds long</span></div><div class='line' id='LC529'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">TCCR1</span> <span class="o">&amp;=</span> <span class="o">~</span><span class="p">(</span><span class="mi">1</span><span class="o">&lt;&lt;</span> <span class="n">CS13</span><span class="p">);</span> <span class="c1">//clear</span></div><div class='line' id='LC530'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">TCCR1</span> <span class="o">|=</span>  <span class="p">(</span><span class="mi">1</span><span class="o">&lt;&lt;</span> <span class="n">CS12</span><span class="p">);</span> <span class="c1">//set</span></div><div class='line' id='LC531'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">TCCR1</span> <span class="o">&amp;=</span> <span class="o">~</span><span class="p">(</span><span class="mi">1</span><span class="o">&lt;&lt;</span> <span class="n">CS11</span><span class="p">);</span> <span class="c1">//clear</span></div><div class='line' id='LC532'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">TCCR1</span> <span class="o">&amp;=</span> <span class="o">~</span><span class="p">(</span><span class="mi">1</span><span class="o">&lt;&lt;</span> <span class="n">CS10</span><span class="p">);</span> <span class="c1">//clear</span></div><div class='line' id='LC533'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="err">#</span><span class="k">else</span></div><div class='line' id='LC534'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//unsupported clock speed</span></div><div class='line' id='LC535'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//TODO: find a way to have the compiler stop compiling and bark at the user</span></div><div class='line' id='LC536'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="err">#</span><span class="n">endif</span></div><div class='line' id='LC537'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="err">#</span><span class="n">endif</span></div><div class='line' id='LC538'><span class="p">}</span><span class="c1">//end setupTimerPrescaler</span></div><div class='line' id='LC539'><br/></div><div class='line' id='LC540'><br/></div><div class='line' id='LC541'><span class="c1">//=============================================================================</span></div><div class='line' id='LC542'><span class="c1">// FUNCTION:    void initServoArray()</span></div><div class='line' id='LC543'><span class="c1">//</span></div><div class='line' id='LC544'><span class="c1">// DESCRIPTION: Sets default values to each element of the servoRegistry array</span></div><div class='line' id='LC545'><span class="c1">//</span></div><div class='line' id='LC546'><span class="c1">// INPUT:       Nothing</span></div><div class='line' id='LC547'><span class="c1">//</span></div><div class='line' id='LC548'><span class="c1">// RETURNS:     Nothing</span></div><div class='line' id='LC549'><span class="c1">//</span></div><div class='line' id='LC550'><span class="c1">//=============================================================================</span></div><div class='line' id='LC551'><span class="kt">void</span> <span class="n">ServoSequencer</span><span class="o">::</span><span class="n">initServoArray</span><span class="p">()</span></div><div class='line' id='LC552'><span class="p">{</span></div><div class='line' id='LC553'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//init the Servo Registry array</span></div><div class='line' id='LC554'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">for</span><span class="p">(</span><span class="kt">uint8_t</span> <span class="n">i</span> <span class="o">=</span> <span class="mi">0</span><span class="p">;</span> <span class="n">i</span> <span class="o">&lt;</span> <span class="n">kMaxNumberOfServosSupported</span><span class="p">;</span> <span class="o">++</span><span class="n">i</span><span class="p">)</span></div><div class='line' id='LC555'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="p">{</span></div><div class='line' id='LC556'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">servoRegistry</span><span class="p">[</span><span class="n">i</span><span class="p">].</span><span class="n">pulseLengthInTicks</span> <span class="o">=</span> <span class="mi">128</span><span class="p">;</span></div><div class='line' id='LC557'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">servoRegistry</span><span class="p">[</span><span class="n">i</span><span class="p">].</span><span class="n">pin</span> <span class="o">=</span> <span class="mi">0</span><span class="p">;</span></div><div class='line' id='LC558'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">servoRegistry</span><span class="p">[</span><span class="n">i</span><span class="p">].</span><span class="n">enabled</span> <span class="o">=</span> <span class="nb">false</span><span class="p">;</span></div><div class='line' id='LC559'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">servoRegistry</span><span class="p">[</span><span class="n">i</span><span class="p">].</span><span class="n">slotOccupied</span> <span class="o">=</span> <span class="nb">false</span><span class="p">;</span></div><div class='line' id='LC560'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="p">}</span></div><div class='line' id='LC561'><br/></div><div class='line' id='LC562'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">servoArrayIsInited</span> <span class="o">=</span> <span class="nb">true</span><span class="p">;</span></div><div class='line' id='LC563'><span class="p">}</span><span class="c1">//end initServoArray</span></div><div class='line' id='LC564'><br/></div><div class='line' id='LC565'><br/></div><div class='line' id='LC566'><span class="c1">//=============================================================================</span></div><div class='line' id='LC567'><span class="c1">// FUNCTION:    void timerCompareMatchISR()</span></div><div class='line' id='LC568'><span class="c1">//</span></div><div class='line' id='LC569'><span class="c1">// DESCRIPTION: Interrupt service routine for timer0 compare A match.</span></div><div class='line' id='LC570'><span class="c1">//              This is where the magic happens.</span></div><div class='line' id='LC571'><span class="c1">//</span></div><div class='line' id='LC572'><span class="c1">// INPUT:       Nothing</span></div><div class='line' id='LC573'><span class="c1">//</span></div><div class='line' id='LC574'><span class="c1">// RETURNS:     Nothing</span></div><div class='line' id='LC575'><span class="c1">//=============================================================================</span></div><div class='line' id='LC576'><span class="kt">void</span> <span class="n">ServoSequencer</span><span class="o">::</span><span class="n">timerCompareMatchISR</span><span class="p">()</span></div><div class='line' id='LC577'><span class="p">{</span></div><div class='line' id='LC578'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">switch</span> <span class="p">(</span><span class="n">state</span><span class="p">)</span></div><div class='line' id='LC579'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="p">{</span></div><div class='line' id='LC580'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">case</span> <span class="n">WAITING_TO_SET_PIN_HIGH</span>:</div><div class='line' id='LC581'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//go to the next servo in the registry</span></div><div class='line' id='LC582'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="o">++</span><span class="n">servoIndex</span><span class="p">;</span></div><div class='line' id='LC583'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//if we are the end of the registry, go to the beginning of it</span></div><div class='line' id='LC584'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">if</span><span class="p">(</span><span class="n">servoIndex</span> <span class="o">==</span> <span class="n">kMaxNumberOfServosSupported</span><span class="p">)</span></div><div class='line' id='LC585'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="p">{</span></div><div class='line' id='LC586'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">servoIndex</span> <span class="o">=</span> <span class="mi">0</span><span class="p">;</span></div><div class='line' id='LC587'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="p">}</span></div><div class='line' id='LC588'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">else</span></div><div class='line' id='LC589'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="p">{</span></div><div class='line' id='LC590'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//we are not at the end, leave the servo index as is</span></div><div class='line' id='LC591'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="p">}</span></div><div class='line' id='LC592'><br/></div><div class='line' id='LC593'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//if this servo is enabled set the pin high</span></div><div class='line' id='LC594'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">if</span><span class="p">(</span> <span class="n">servoRegistry</span><span class="p">[</span><span class="n">servoIndex</span><span class="p">].</span><span class="n">enabled</span> <span class="o">==</span> <span class="nb">true</span> <span class="p">)</span></div><div class='line' id='LC595'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="p">{</span></div><div class='line' id='LC596'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">PORTB</span> <span class="o">|=</span> <span class="p">(</span><span class="mi">1</span> <span class="o">&lt;&lt;</span> <span class="n">servoRegistry</span><span class="p">[</span><span class="n">servoIndex</span><span class="p">].</span><span class="n">pin</span><span class="p">);</span></div><div class='line' id='LC597'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="p">}</span></div><div class='line' id='LC598'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">else</span></div><div class='line' id='LC599'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="p">{</span></div><div class='line' id='LC600'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//This servo position is not enabled, don&#39;t manipulate the pin</span></div><div class='line' id='LC601'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="p">}</span></div><div class='line' id='LC602'><br/></div><div class='line' id='LC603'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//reset the counter to 0</span></div><div class='line' id='LC604'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">TCNTn</span>  <span class="o">=</span> <span class="mi">0</span><span class="p">;</span></div><div class='line' id='LC605'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//set the compare value to 64 (512 us). This is the constant pulse offset.</span></div><div class='line' id='LC606'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">OCRnx</span> <span class="o">=</span> <span class="mi">64</span> <span class="o">-</span> <span class="n">TRIM_DURATION</span><span class="p">;</span> <span class="c1">//trim off 4 ticks (32us), this is about the total combined time we spent inside this ISR;</span></div><div class='line' id='LC607'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//update our state</span></div><div class='line' id='LC608'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">state</span> <span class="o">=</span> <span class="n">WAITING_FOR_512_MARK</span><span class="p">;</span></div><div class='line' id='LC609'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">break</span><span class="p">;</span></div><div class='line' id='LC610'><br/></div><div class='line' id='LC611'><br/></div><div class='line' id='LC612'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">case</span> <span class="n">WAITING_FOR_512_MARK</span>:</div><div class='line' id='LC613'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//set the compare value to the additional amount of timer ticks the pulse should last</span></div><div class='line' id='LC614'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">OCRnx</span> <span class="o">=</span> <span class="n">servoRegistry</span><span class="p">[</span><span class="n">servoIndex</span><span class="p">].</span><span class="n">pulseLengthInTicks</span><span class="p">;</span></div><div class='line' id='LC615'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//update our state</span></div><div class='line' id='LC616'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">state</span> <span class="o">=</span> <span class="n">WAITING_TO_SET_PIN_LOW</span><span class="p">;</span></div><div class='line' id='LC617'><br/></div><div class='line' id='LC618'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//reset the counter to 0</span></div><div class='line' id='LC619'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">TCNTn</span>  <span class="o">=</span> <span class="mi">0</span><span class="p">;</span></div><div class='line' id='LC620'><br/></div><div class='line' id='LC621'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//Did we just set OCRnx to zero?</span></div><div class='line' id='LC622'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">if</span><span class="p">(</span><span class="n">OCRnx</span> <span class="o">==</span> <span class="mi">0</span><span class="p">)</span></div><div class='line' id='LC623'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="p">{</span></div><div class='line' id='LC624'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//Since we are setting OCRnx and TCNTn to 0 we are not going to get an interrupt</span></div><div class='line' id='LC625'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//until the counter overflows and goes back to 0.</span></div><div class='line' id='LC626'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//set the counter its highest value, to have it overflow right away.</span></div><div class='line' id='LC627'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">TCNTn</span> <span class="o">=</span> <span class="mh">0xFF</span><span class="p">;</span></div><div class='line' id='LC628'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//This will cause this interrupt to fire again almost immediately (at the next timer tick)</span></div><div class='line' id='LC629'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="p">}</span></div><div class='line' id='LC630'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">else</span></div><div class='line' id='LC631'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="p">{</span></div><div class='line' id='LC632'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//otherwise we need to clear the OCF0A flag because it is possible that the</span></div><div class='line' id='LC633'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//counter value incremented and matched the output compare value while this</span></div><div class='line' id='LC634'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//function was being executed</span></div><div class='line' id='LC635'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">TIFR</span> <span class="o">=</span> <span class="p">(</span><span class="mi">1</span> <span class="o">&lt;&lt;</span> <span class="n">OCF0A</span><span class="p">);</span>  <span class="c1">// write logical 1 to the OCF0A flag to clear it</span></div><div class='line' id='LC636'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">// also have to write 0 to all other bits for this to work.</span></div><div class='line' id='LC637'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="p">}</span></div><div class='line' id='LC638'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">break</span><span class="p">;</span></div><div class='line' id='LC639'><br/></div><div class='line' id='LC640'><br/></div><div class='line' id='LC641'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">case</span> <span class="n">WAITING_TO_SET_PIN_LOW</span>:</div><div class='line' id='LC642'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//if this servo is enabled set the pin low</span></div><div class='line' id='LC643'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">if</span><span class="p">(</span> <span class="n">servoRegistry</span><span class="p">[</span><span class="n">servoIndex</span><span class="p">].</span><span class="n">enabled</span> <span class="o">==</span> <span class="nb">true</span> <span class="p">)</span></div><div class='line' id='LC644'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="p">{</span></div><div class='line' id='LC645'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">PORTB</span> <span class="o">&amp;=</span> <span class="o">~</span><span class="p">(</span><span class="mi">1</span> <span class="o">&lt;&lt;</span> <span class="n">servoRegistry</span><span class="p">[</span><span class="n">servoIndex</span><span class="p">].</span><span class="n">pin</span><span class="p">);</span></div><div class='line' id='LC646'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="p">}</span></div><div class='line' id='LC647'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">else</span></div><div class='line' id='LC648'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="p">{</span></div><div class='line' id='LC649'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//This servo position is not enabled, don&#39;t manipulate the pin</span></div><div class='line' id='LC650'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="p">}</span></div><div class='line' id='LC651'><br/></div><div class='line' id='LC652'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//check if the length of this pulse is 2048 microseconds or longer</span></div><div class='line' id='LC653'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">if</span><span class="p">(</span> <span class="p">(</span><span class="mi">64</span> <span class="o">+</span> <span class="n">servoRegistry</span><span class="p">[</span><span class="n">servoIndex</span><span class="p">].</span><span class="n">pulseLengthInTicks</span><span class="p">)</span> <span class="o">&gt;</span> <span class="mi">255</span> <span class="p">)</span></div><div class='line' id='LC654'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="p">{</span></div><div class='line' id='LC655'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//This pulse length has passed the 2048 us mark, so we skip state WAITING_FOR_2048_MARK</span></div><div class='line' id='LC656'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//update state</span></div><div class='line' id='LC657'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">state</span> <span class="o">=</span> <span class="n">WAITING_TO_SET_PIN_HIGH</span><span class="p">;</span></div><div class='line' id='LC658'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//set the compare value to the amount of time (in timer ticks) we need to wait to reach</span></div><div class='line' id='LC659'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//4096 microseconds mark</span></div><div class='line' id='LC660'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//which is 512 minus the total pulse length. (resulting number will be between 0 and 255 inclusive)</span></div><div class='line' id='LC661'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">OCRnx</span> <span class="o">=</span> <span class="mi">512</span> <span class="o">-</span> <span class="p">(</span><span class="mi">64</span> <span class="o">+</span> <span class="n">servoRegistry</span><span class="p">[</span><span class="n">servoIndex</span><span class="p">].</span><span class="n">pulseLengthInTicks</span><span class="p">);</span></div><div class='line' id='LC662'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="p">}</span></div><div class='line' id='LC663'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">else</span></div><div class='line' id='LC664'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="p">{</span></div><div class='line' id='LC665'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//This pulse length has not reached the 2048 us mark, therefor we have to get to that mark first</span></div><div class='line' id='LC666'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//update state</span></div><div class='line' id='LC667'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">state</span> <span class="o">=</span> <span class="n">WAITING_FOR_2048_MARK</span><span class="p">;</span></div><div class='line' id='LC668'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//set OCRnx to the amount of time (in timer ticks) we have to wait to reach this mark</span></div><div class='line' id='LC669'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//which is 255 minus the total pulse length</span></div><div class='line' id='LC670'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">OCRnx</span> <span class="o">=</span> <span class="mi">255</span> <span class="o">-</span> <span class="p">(</span><span class="mi">64</span> <span class="o">+</span> <span class="n">servoRegistry</span><span class="p">[</span><span class="n">servoIndex</span><span class="p">].</span><span class="n">pulseLengthInTicks</span><span class="p">);</span></div><div class='line' id='LC671'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="p">}</span></div><div class='line' id='LC672'><br/></div><div class='line' id='LC673'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//reset the counter to 0</span></div><div class='line' id='LC674'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">TCNTn</span>  <span class="o">=</span> <span class="mi">0</span><span class="p">;</span></div><div class='line' id='LC675'><br/></div><div class='line' id='LC676'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">break</span><span class="p">;</span></div><div class='line' id='LC677'><br/></div><div class='line' id='LC678'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">case</span> <span class="n">WAITING_FOR_2048_MARK</span>:</div><div class='line' id='LC679'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//update state</span></div><div class='line' id='LC680'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">state</span> <span class="o">=</span> <span class="n">WAITING_TO_SET_PIN_HIGH</span><span class="p">;</span></div><div class='line' id='LC681'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//reset the counter to 0</span></div><div class='line' id='LC682'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">TCNTn</span>  <span class="o">=</span> <span class="mi">0</span><span class="p">;</span></div><div class='line' id='LC683'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//set the compare value to the longest length of time, 255 ticks, or 2040 microseconds</span></div><div class='line' id='LC684'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//This will take us to the ~4096 microsecond mark,</span></div><div class='line' id='LC685'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//at which point the cycle starts again with the next servo slot.</span></div><div class='line' id='LC686'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">OCRnx</span> <span class="o">=</span> <span class="mi">255</span><span class="p">;</span></div><div class='line' id='LC687'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">break</span><span class="p">;</span></div><div class='line' id='LC688'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="p">}</span><span class="c1">//end switch</span></div><div class='line' id='LC689'><span class="p">}</span><span class="c1">//end timerCompareMatchISR</span></div><div class='line' id='LC690'><br/></div><div class='line' id='LC691'><br/></div><div class='line' id='LC692'><br/></div><div class='line' id='LC693'><br/></div><div class='line' id='LC694'><span class="c1">//=============================================================================</span></div><div class='line' id='LC695'><span class="c1">// Non Memeber Functions</span></div><div class='line' id='LC696'><span class="c1">//=============================================================================</span></div><div class='line' id='LC697'><br/></div><div class='line' id='LC698'><span class="c1">//only define this ISR if we are using TIMER0</span></div><div class='line' id='LC699'><span class="cp">#ifdef USE_TIMER0</span></div><div class='line' id='LC700'><span class="c1">//=============================================================================</span></div><div class='line' id='LC701'><span class="c1">// FUNCTION:    Interrupt service routine for timer0 compare A match</span></div><div class='line' id='LC702'><span class="c1">//</span></div><div class='line' id='LC703'><span class="c1">// DESCRIPTION: AVR Libc provided function that is vectored into when the</span></div><div class='line' id='LC704'><span class="c1">//              timer0 compare A match interrupt fires.</span></div><div class='line' id='LC705'><span class="c1">//</span></div><div class='line' id='LC706'><span class="c1">// INPUT:       Nothing</span></div><div class='line' id='LC707'><span class="c1">//</span></div><div class='line' id='LC708'><span class="c1">// RETURNS:     Nothing</span></div><div class='line' id='LC709'><span class="c1">//=============================================================================</span></div><div class='line' id='LC710'><span class="n">ISR</span><span class="p">(</span><span class="n">TIM0_COMPA_vect</span><span class="p">)</span></div><div class='line' id='LC711'><span class="p">{</span></div><div class='line' id='LC712'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">ServoSequencer</span><span class="o">::</span><span class="n">timerCompareMatchISR</span><span class="p">();</span></div><div class='line' id='LC713'><span class="p">}</span><span class="c1">//end ISR TIM0_COMPA_vect</span></div><div class='line' id='LC714'><span class="cp">#endif</span></div><div class='line' id='LC715'><br/></div><div class='line' id='LC716'><br/></div><div class='line' id='LC717'><br/></div><div class='line' id='LC718'><span class="c1">//only define this ISR if we are using TIMER1</span></div><div class='line' id='LC719'><span class="cp">#ifdef USE_TIMER1</span></div><div class='line' id='LC720'><span class="c1">//=============================================================================</span></div><div class='line' id='LC721'><span class="c1">// FUNCTION:    Interrupt service routine for timer1 compare A match</span></div><div class='line' id='LC722'><span class="c1">//</span></div><div class='line' id='LC723'><span class="c1">// DESCRIPTION: AVR Libc provided function that is vectored into when the</span></div><div class='line' id='LC724'><span class="c1">//              timer0 compare A match interrupt fires.</span></div><div class='line' id='LC725'><span class="c1">//</span></div><div class='line' id='LC726'><span class="c1">// INPUT:       Nothing</span></div><div class='line' id='LC727'><span class="c1">//</span></div><div class='line' id='LC728'><span class="c1">// RETURNS:     Nothing</span></div><div class='line' id='LC729'><span class="c1">//=============================================================================</span></div><div class='line' id='LC730'><span class="n">ISR</span><span class="p">(</span><span class="n">TIM1_COMPA_vect</span><span class="p">)</span></div><div class='line' id='LC731'><span class="p">{</span></div><div class='line' id='LC732'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">ServoSequencer</span><span class="o">::</span><span class="n">timerCompareMatchISR</span><span class="p">();</span></div><div class='line' id='LC733'><span class="p">}</span><span class="c1">//end ISR TIM0_COMPA_vect</span></div><div class='line' id='LC734'><span class="cp">#endif</span></div><div class='line' id='LC735'><br/></div><div class='line' id='LC736'><br/></div><div class='line' id='LC737'><br/></div><div class='line' id='LC738'><br/></div><div class='line' id='LC739'><br/></div><div class='line' id='LC740'><br/></div><div class='line' id='LC741'><br/></div><div class='line' id='LC742'><br/></div><div class='line' id='LC743'><br/></div><div class='line' id='LC744'><br/></div><div class='line' id='LC745'><br/></div><div class='line' id='LC746'><br/></div><div class='line' id='LC747'><br/></div><div class='line' id='LC748'><br/></div><div class='line' id='LC749'><br/></div><div class='line' id='LC750'><br/></div><div class='line' id='LC751'><br/></div><div class='line' id='LC752'><br/></div><div class='line' id='LC753'><br/></div><div class='line' id='LC754'><br/></div><div class='line' id='LC755'><br/></div><div class='line' id='LC756'><br/></div><div class='line' id='LC757'><br/></div><div class='line' id='LC758'><br/></div><div class='line' id='LC759'><br/></div><div class='line' id='LC760'><br/></div><div class='line' id='LC761'><br/></div><div class='line' id='LC762'><br/></div><div class='line' id='LC763'><br/></div><div class='line' id='LC764'><br/></div><div class='line' id='LC765'><br/></div><div class='line' id='LC766'><br/></div><div class='line' id='LC767'><br/></div><div class='line' id='LC768'><span class="c1">//=============================================================================</span></div><div class='line' id='LC769'><span class="c1">// Servo Class Functions</span></div><div class='line' id='LC770'><span class="c1">//=============================================================================</span></div><div class='line' id='LC771'><br/></div><div class='line' id='LC772'><span class="c1">//=============================================================================</span></div><div class='line' id='LC773'><span class="c1">// FUNCTION:    constructor</span></div><div class='line' id='LC774'><span class="c1">//</span></div><div class='line' id='LC775'><span class="c1">// DESCRIPTION: Constructor</span></div><div class='line' id='LC776'><span class="c1">//              Also registers with the ServoSequencer.</span></div><div class='line' id='LC777'><span class="c1">//</span></div><div class='line' id='LC778'><span class="c1">// INPUT:       Nothing</span></div><div class='line' id='LC779'><span class="c1">//</span></div><div class='line' id='LC780'><span class="c1">// RETURNS:     Nothing</span></div><div class='line' id='LC781'><span class="c1">//</span></div><div class='line' id='LC782'><span class="c1">//=============================================================================</span></div><div class='line' id='LC783'><span class="n">Servo8Bit</span><span class="o">::</span><span class="n">Servo8Bit</span><span class="p">()</span></div><div class='line' id='LC784'><span class="o">:</span><span class="n">invalidServoNumber</span><span class="p">(</span><span class="n">ServoSequencer</span><span class="o">::</span><span class="n">kInvalidServoIndex</span><span class="p">),</span></div><div class='line' id='LC785'>&nbsp;<span class="n">myServoNumber</span><span class="p">(</span><span class="n">invalidServoNumber</span><span class="p">),</span></div><div class='line' id='LC786'>&nbsp;<span class="n">myMin</span><span class="p">(</span><span class="n">kDefaultMinimalPulse</span><span class="p">),</span></div><div class='line' id='LC787'>&nbsp;<span class="n">myMax</span><span class="p">(</span><span class="n">kDefaultMaximumPulse</span><span class="p">)</span></div><div class='line' id='LC788'><span class="p">{</span></div><div class='line' id='LC789'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">myServoNumber</span> <span class="o">=</span> <span class="n">ServoSequencer</span><span class="o">::</span><span class="n">registerServo</span><span class="p">();</span></div><div class='line' id='LC790'><span class="p">}</span><span class="c1">//end constructor</span></div><div class='line' id='LC791'><br/></div><div class='line' id='LC792'><br/></div><div class='line' id='LC793'><span class="c1">//=============================================================================</span></div><div class='line' id='LC794'><span class="c1">// FUNCTION:    void attach(uint8_t pin)</span></div><div class='line' id='LC795'><span class="c1">//</span></div><div class='line' id='LC796'><span class="c1">// DESCRIPTION: Attaches a servo motor to an i/o pin on Port B.</span></div><div class='line' id='LC797'><span class="c1">//</span></div><div class='line' id='LC798'><span class="c1">// INPUT:       pin - which pin on portB to attach to</span></div><div class='line' id='LC799'><span class="c1">//</span></div><div class='line' id='LC800'><span class="c1">// RETURNS:     The servo number of this servo.</span></div><div class='line' id='LC801'><span class="c1">//</span></div><div class='line' id='LC802'><span class="c1">//=============================================================================</span></div><div class='line' id='LC803'><span class="kt">uint8_t</span> <span class="n">Servo8Bit</span><span class="o">::</span><span class="n">attach</span><span class="p">(</span><span class="kt">uint8_t</span> <span class="n">pin</span><span class="p">)</span></div><div class='line' id='LC804'><span class="p">{</span></div><div class='line' id='LC805'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//make sure we have a valid servo number. If it&#39;s invalid then exit doing nothing.</span></div><div class='line' id='LC806'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">if</span><span class="p">(</span><span class="n">myServoNumber</span> <span class="o">==</span> <span class="n">invalidServoNumber</span><span class="p">)</span> <span class="k">return</span> <span class="mi">0</span><span class="p">;</span></div><div class='line' id='LC807'><br/></div><div class='line' id='LC808'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//LIMITATION: this servo class only works with PORTB, which is the only port</span></div><div class='line' id='LC809'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//on the attiny45 and attiny85</span></div><div class='line' id='LC810'><br/></div><div class='line' id='LC811'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//valid pin values are between 0 and 5, inclusive.</span></div><div class='line' id='LC812'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">if</span><span class="p">(</span> <span class="n">pin</span> <span class="o">&lt;=</span> <span class="mi">5</span> <span class="p">)</span></div><div class='line' id='LC813'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="p">{</span></div><div class='line' id='LC814'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">DDRB</span> <span class="o">|=</span> <span class="p">(</span><span class="mi">1</span><span class="o">&lt;&lt;</span><span class="n">pin</span><span class="p">);</span> <span class="c1">//set pin as output</span></div><div class='line' id='LC815'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//set the servo pin</span></div><div class='line' id='LC816'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">ServoSequencer</span><span class="o">::</span><span class="n">setServoPin</span><span class="p">(</span><span class="n">myServoNumber</span><span class="p">,</span> <span class="n">pin</span><span class="p">);</span></div><div class='line' id='LC817'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//enable the servo to start outputing the pwm wave</span></div><div class='line' id='LC818'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">ServoSequencer</span><span class="o">::</span><span class="n">enableDisableServo</span><span class="p">(</span><span class="n">myServoNumber</span><span class="p">,</span> <span class="nb">true</span><span class="p">);</span></div><div class='line' id='LC819'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="p">}</span></div><div class='line' id='LC820'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">else</span></div><div class='line' id='LC821'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="p">{</span></div><div class='line' id='LC822'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//bad pin value. do nothing.</span></div><div class='line' id='LC823'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="p">}</span></div><div class='line' id='LC824'><br/></div><div class='line' id='LC825'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">return</span> <span class="n">myServoNumber</span><span class="p">;</span></div><div class='line' id='LC826'><br/></div><div class='line' id='LC827'><span class="p">}</span><span class="c1">//end attach</span></div><div class='line' id='LC828'><br/></div><div class='line' id='LC829'><br/></div><div class='line' id='LC830'><br/></div><div class='line' id='LC831'><br/></div><div class='line' id='LC832'><br/></div><div class='line' id='LC833'><span class="c1">//=============================================================================</span></div><div class='line' id='LC834'><span class="c1">// FUNCTION:    uint8_t attach(uint8_t pin, uint16_t min, uint16_t max)</span></div><div class='line' id='LC835'><span class="c1">//</span></div><div class='line' id='LC836'><span class="c1">// DESCRIPTION: Attaches a servo motor to an i/o pin on Port B and also sets</span></div><div class='line' id='LC837'><span class="c1">//              the minimum and maximum pulse length values for this servo.</span></div><div class='line' id='LC838'><span class="c1">//</span></div><div class='line' id='LC839'><span class="c1">// INPUT:       pin - which pin on portB to attach to</span></div><div class='line' id='LC840'><span class="c1">//              min - minimum pulse length to use</span></div><div class='line' id='LC841'><span class="c1">//              max - maximum pulse length to use</span></div><div class='line' id='LC842'><span class="c1">//</span></div><div class='line' id='LC843'><span class="c1">// RETURNS:</span></div><div class='line' id='LC844'><span class="c1">//</span></div><div class='line' id='LC845'><span class="c1">//=============================================================================</span></div><div class='line' id='LC846'><span class="kt">uint8_t</span> <span class="n">Servo8Bit</span><span class="o">::</span><span class="n">attach</span><span class="p">(</span><span class="kt">uint8_t</span> <span class="n">pin</span><span class="p">,</span> <span class="kt">uint16_t</span> <span class="n">newMin</span><span class="p">,</span> <span class="kt">uint16_t</span> <span class="n">newMax</span><span class="p">)</span></div><div class='line' id='LC847'><span class="p">{</span></div><div class='line' id='LC848'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">myMin</span> <span class="o">=</span> <span class="n">newMin</span><span class="p">;</span></div><div class='line' id='LC849'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">myMax</span> <span class="o">=</span> <span class="n">newMax</span><span class="p">;</span></div><div class='line' id='LC850'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">return</span> <span class="nf">attach</span><span class="p">(</span><span class="n">pin</span><span class="p">);</span></div><div class='line' id='LC851'><span class="p">}</span><span class="c1">//end attach with min/max</span></div><div class='line' id='LC852'><br/></div><div class='line' id='LC853'><br/></div><div class='line' id='LC854'><span class="c1">//=============================================================================</span></div><div class='line' id='LC855'><span class="c1">// FUNCTION:    void detach()</span></div><div class='line' id='LC856'><span class="c1">//</span></div><div class='line' id='LC857'><span class="c1">// DESCRIPTION: Stops an attached servos from pulsing its i/o pin.</span></div><div class='line' id='LC858'><span class="c1">//</span></div><div class='line' id='LC859'><span class="c1">// INPUT:       Nothing</span></div><div class='line' id='LC860'><span class="c1">//</span></div><div class='line' id='LC861'><span class="c1">// RETURNS:     Nothing</span></div><div class='line' id='LC862'><span class="c1">//</span></div><div class='line' id='LC863'><span class="c1">//=============================================================================</span></div><div class='line' id='LC864'><span class="kt">void</span> <span class="n">Servo8Bit</span><span class="o">::</span><span class="n">detach</span><span class="p">()</span></div><div class='line' id='LC865'><span class="p">{</span></div><div class='line' id='LC866'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">ServoSequencer</span><span class="o">::</span><span class="n">deregisterServo</span><span class="p">(</span><span class="n">myServoNumber</span><span class="p">);</span></div><div class='line' id='LC867'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">myServoNumber</span> <span class="o">=</span> <span class="n">invalidServoNumber</span><span class="p">;</span></div><div class='line' id='LC868'><span class="p">}</span></div><div class='line' id='LC869'><br/></div><div class='line' id='LC870'><br/></div><div class='line' id='LC871'><span class="c1">//=============================================================================</span></div><div class='line' id='LC872'><span class="c1">// FUNCTION:    void write(uint16_t value)</span></div><div class='line' id='LC873'><span class="c1">//</span></div><div class='line' id='LC874'><span class="c1">// DESCRIPTION: Sets the servo angle in degrees.</span></div><div class='line' id='LC875'><span class="c1">//              invalid angle that is valid as pulse in microseconds is</span></div><div class='line' id='LC876'><span class="c1">//              treated as microseconds.</span></div><div class='line' id='LC877'><span class="c1">//</span></div><div class='line' id='LC878'><span class="c1">// INPUT:       value - position for the servo to move to</span></div><div class='line' id='LC879'><span class="c1">//</span></div><div class='line' id='LC880'><span class="c1">// RETURNS:     Nothing</span></div><div class='line' id='LC881'><span class="c1">//</span></div><div class='line' id='LC882'><span class="c1">//=============================================================================</span></div><div class='line' id='LC883'><span class="kt">void</span> <span class="n">Servo8Bit</span><span class="o">::</span><span class="n">write</span><span class="p">(</span><span class="kt">uint16_t</span> <span class="n">value</span><span class="p">)</span></div><div class='line' id='LC884'><span class="p">{</span></div><div class='line' id='LC885'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//make sure we have a valid servo number. If it&#39;s invalid then exit doing nothing.</span></div><div class='line' id='LC886'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">if</span><span class="p">(</span><span class="n">myServoNumber</span> <span class="o">==</span> <span class="n">invalidServoNumber</span><span class="p">)</span> <span class="k">return</span><span class="p">;</span></div><div class='line' id='LC887'><br/></div><div class='line' id='LC888'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//for now, only accept angles, and angles that are between 0 and 200 degrees</span></div><div class='line' id='LC889'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">if</span><span class="p">(</span> <span class="n">value</span> <span class="o">&gt;</span> <span class="mi">180</span> <span class="p">)</span></div><div class='line' id='LC890'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="p">{</span></div><div class='line' id='LC891'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//treat this number as microseconds</span></div><div class='line' id='LC892'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">writeMicroseconds</span><span class="p">(</span> <span class="n">value</span> <span class="p">);</span></div><div class='line' id='LC893'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="p">}</span></div><div class='line' id='LC894'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">else</span></div><div class='line' id='LC895'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="p">{</span></div><div class='line' id='LC896'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//treat this number as degrees</span></div><div class='line' id='LC897'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="kt">uint16_t</span> <span class="n">servoPulseLengthInUs</span> <span class="o">=</span> <span class="n">map</span><span class="p">(</span><span class="n">value</span><span class="p">,</span> <span class="mi">0</span><span class="p">,</span> <span class="mi">180</span><span class="p">,</span> <span class="n">myMin</span><span class="p">,</span> <span class="n">myMax</span><span class="p">);</span></div><div class='line' id='LC898'>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">writeMicroseconds</span><span class="p">(</span> <span class="n">servoPulseLengthInUs</span> <span class="p">);</span></div><div class='line' id='LC899'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="p">}</span></div><div class='line' id='LC900'><span class="p">}</span><span class="c1">//end write</span></div><div class='line' id='LC901'><br/></div><div class='line' id='LC902'><br/></div><div class='line' id='LC903'><span class="c1">//=============================================================================</span></div><div class='line' id='LC904'><span class="c1">// FUNCTION:    void writeMicroseconds(uint16_t value)</span></div><div class='line' id='LC905'><span class="c1">//</span></div><div class='line' id='LC906'><span class="c1">// DESCRIPTION: Sets the servo pulse width in microseconds</span></div><div class='line' id='LC907'><span class="c1">//</span></div><div class='line' id='LC908'><span class="c1">// INPUT:       value - the pulse width of the servo pulse in microseconds</span></div><div class='line' id='LC909'><span class="c1">//</span></div><div class='line' id='LC910'><span class="c1">// RETURNS:     Nothing</span></div><div class='line' id='LC911'><span class="c1">//</span></div><div class='line' id='LC912'><span class="c1">//=============================================================================</span></div><div class='line' id='LC913'><span class="kt">void</span> <span class="n">Servo8Bit</span><span class="o">::</span><span class="n">writeMicroseconds</span><span class="p">(</span><span class="kt">uint16_t</span> <span class="n">value</span><span class="p">)</span></div><div class='line' id='LC914'><span class="p">{</span></div><div class='line' id='LC915'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//make sure we have a valid servo number. If it&#39;s invalid then exit doing nothing.</span></div><div class='line' id='LC916'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">if</span><span class="p">(</span><span class="n">myServoNumber</span> <span class="o">==</span> <span class="n">invalidServoNumber</span><span class="p">)</span> <span class="k">return</span><span class="p">;</span></div><div class='line' id='LC917'><br/></div><div class='line' id='LC918'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="n">ServoSequencer</span><span class="o">::</span><span class="n">setServoPulseLength</span><span class="p">(</span><span class="n">myServoNumber</span><span class="p">,</span> <span class="n">value</span> <span class="p">);</span></div><div class='line' id='LC919'><span class="p">}</span><span class="c1">//end writeMicroseconds</span></div><div class='line' id='LC920'><br/></div><div class='line' id='LC921'><br/></div><div class='line' id='LC922'><br/></div><div class='line' id='LC923'><br/></div><div class='line' id='LC924'><br/></div><div class='line' id='LC925'><span class="c1">//=============================================================================</span></div><div class='line' id='LC926'><span class="c1">// FUNCTION:    uint16_t readMicroseconds()</span></div><div class='line' id='LC927'><span class="c1">//</span></div><div class='line' id='LC928'><span class="c1">// DESCRIPTION: Gets the last written servo pulse width in microseconds.</span></div><div class='line' id='LC929'><span class="c1">//</span></div><div class='line' id='LC930'><span class="c1">// INPUT:       Nothing</span></div><div class='line' id='LC931'><span class="c1">//</span></div><div class='line' id='LC932'><span class="c1">// RETURNS:     The pulse width in microseconds</span></div><div class='line' id='LC933'><span class="c1">//</span></div><div class='line' id='LC934'><span class="c1">//=============================================================================</span></div><div class='line' id='LC935'><span class="kt">uint16_t</span> <span class="n">Servo8Bit</span><span class="o">::</span><span class="n">readMicroseconds</span><span class="p">()</span></div><div class='line' id='LC936'><span class="p">{</span></div><div class='line' id='LC937'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//make sure we have a valid servo number. If it&#39;s invalid then exit doing nothing.</span></div><div class='line' id='LC938'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">if</span><span class="p">(</span><span class="n">myServoNumber</span> <span class="o">==</span> <span class="n">invalidServoNumber</span><span class="p">)</span> <span class="k">return</span> <span class="mi">0</span><span class="p">;</span></div><div class='line' id='LC939'><br/></div><div class='line' id='LC940'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">return</span> <span class="n">ServoSequencer</span><span class="o">::</span><span class="n">getServoPulseLength</span><span class="p">(</span><span class="n">myServoNumber</span><span class="p">);</span></div><div class='line' id='LC941'><span class="p">}</span><span class="c1">//end readMicroseconds</span></div><div class='line' id='LC942'><br/></div><div class='line' id='LC943'><br/></div><div class='line' id='LC944'><span class="c1">//=============================================================================</span></div><div class='line' id='LC945'><span class="c1">// FUNCTION:    uint16_t read()</span></div><div class='line' id='LC946'><span class="c1">//</span></div><div class='line' id='LC947'><span class="c1">// DESCRIPTION: Gets the last written servo pulse width as an angle between 0 and 180.</span></div><div class='line' id='LC948'><span class="c1">//</span></div><div class='line' id='LC949'><span class="c1">// INPUT:       Nothing</span></div><div class='line' id='LC950'><span class="c1">//</span></div><div class='line' id='LC951'><span class="c1">// RETURNS:     Angle between 0 and 180</span></div><div class='line' id='LC952'><span class="c1">//</span></div><div class='line' id='LC953'><span class="c1">//=============================================================================</span></div><div class='line' id='LC954'><span class="kt">uint16_t</span> <span class="n">Servo8Bit</span><span class="o">::</span><span class="n">read</span><span class="p">()</span></div><div class='line' id='LC955'><span class="p">{</span></div><div class='line' id='LC956'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//make sure we have a valid servo number. If it&#39;s invalid then exit doing nothing.</span></div><div class='line' id='LC957'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">if</span><span class="p">(</span><span class="n">myServoNumber</span> <span class="o">==</span> <span class="n">invalidServoNumber</span><span class="p">)</span> <span class="k">return</span> <span class="mi">0</span><span class="p">;</span></div><div class='line' id='LC958'><br/></div><div class='line' id='LC959'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="kt">uint16_t</span> <span class="n">servoPulseLengthInUs</span> <span class="o">=</span> <span class="n">readMicroseconds</span><span class="p">();</span></div><div class='line' id='LC960'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="kt">uint16_t</span> <span class="n">servoPositionInDegrees</span> <span class="o">=</span> <span class="n">map</span><span class="p">(</span><span class="n">servoPulseLengthInUs</span><span class="p">,</span> <span class="n">myMin</span><span class="p">,</span> <span class="n">myMax</span><span class="p">,</span> <span class="mi">0</span><span class="p">,</span> <span class="mi">180</span><span class="p">);</span></div><div class='line' id='LC961'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">return</span> <span class="n">servoPositionInDegrees</span><span class="p">;</span></div><div class='line' id='LC962'><span class="p">}</span><span class="c1">//end read</span></div><div class='line' id='LC963'><br/></div><div class='line' id='LC964'><br/></div><div class='line' id='LC965'><span class="c1">//=============================================================================</span></div><div class='line' id='LC966'><span class="c1">// FUNCTION:    bool attached()</span></div><div class='line' id='LC967'><span class="c1">//</span></div><div class='line' id='LC968'><span class="c1">// DESCRIPTION: Returns true if there is a servo attached.</span></div><div class='line' id='LC969'><span class="c1">//</span></div><div class='line' id='LC970'><span class="c1">// INPUT:       Nothing</span></div><div class='line' id='LC971'><span class="c1">//</span></div><div class='line' id='LC972'><span class="c1">// RETURNS:     true, if attached</span></div><div class='line' id='LC973'><span class="c1">//              false, otherwise</span></div><div class='line' id='LC974'><span class="c1">//</span></div><div class='line' id='LC975'><span class="c1">//=============================================================================</span></div><div class='line' id='LC976'><span class="kt">bool</span> <span class="n">Servo8Bit</span><span class="o">::</span><span class="n">attached</span><span class="p">()</span></div><div class='line' id='LC977'><span class="p">{</span></div><div class='line' id='LC978'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="c1">//make sure we have a valid servo number. If it&#39;s invalid then exit doing nothing.</span></div><div class='line' id='LC979'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">if</span><span class="p">(</span><span class="n">myServoNumber</span> <span class="o">==</span> <span class="n">invalidServoNumber</span><span class="p">)</span> <span class="k">return</span> <span class="nb">false</span><span class="p">;</span></div><div class='line' id='LC980'><br/></div><div class='line' id='LC981'>&nbsp;&nbsp;&nbsp;&nbsp;<span class="k">return</span> <span class="n">ServoSequencer</span><span class="o">::</span><span class="n">isEnabled</span><span class="p">(</span><span class="n">myServoNumber</span><span class="p">);</span></div><div class='line' id='LC982'><span class="p">}</span><span class="c1">//end attached</span></div><div class='line' id='LC983'><br/></div><div class='line' id='LC984'><br/></div><div class='line' id='LC985'><span class="c1">//=============================================================================</span></div><div class='line' id='LC986'><span class="c1">// FUNCTION:    long map(long x, long in_min, long in_max, long out_min, long out_max)</span></div><div class='line' id='LC987'><span class="c1">//</span></div><div class='line' id='LC988'><span class="c1">// DESCRIPTION: Our own map function, so that we don&#39;t have to get it from some library.</span></div><div class='line' id='LC989'><span class="c1">//              Re-maps a number from one range to another.</span></div><div class='line' id='LC990'><span class="c1">//              Does not constrain values to within the range.</span></div><div class='line' id='LC991'><span class="c1">//</span></div><div class='line' id='LC992'><span class="c1">// INPUT:       x       - value to map</span></div><div class='line' id='LC993'><span class="c1">//              in_min  - from low</span></div><div class='line' id='LC994'><span class="c1">//              in_max  - from high</span></div><div class='line' id='LC995'><span class="c1">//              out_min - to low</span></div><div class='line' id='LC996'><span class="c1">//              out_max - to high</span></div><div class='line' id='LC997'><span class="c1">//</span></div><div class='line' id='LC998'><span class="c1">// RETURNS:     re-maped value</span></div><div class='line' id='LC999'><span class="c1">//</span></div><div class='line' id='LC1000'><span class="c1">//=============================================================================</span></div><div class='line' id='LC1001'><span class="kt">long</span> <span class="n">Servo8Bit</span><span class="o">::</span><span class="n">map</span><span class="p">(</span><span class="kt">long</span> <span class="n">x</span><span class="p">,</span> <span class="kt">long</span> <span class="n">in_min</span><span class="p">,</span> <span class="kt">long</span> <span class="n">in_max</span><span class="p">,</span> <span class="kt">long</span> <span class="n">out_min</span><span class="p">,</span> <span class="kt">long</span> <span class="n">out_max</span><span class="p">)</span></div><div class='line' id='LC1002'><span class="p">{</span></div><div class='line' id='LC1003'>&nbsp;&nbsp;<span class="k">return</span> <span class="p">(</span><span class="n">x</span> <span class="o">-</span> <span class="n">in_min</span><span class="p">)</span> <span class="o">*</span> <span class="p">(</span><span class="n">out_max</span> <span class="o">-</span> <span class="n">out_min</span><span class="p">)</span> <span class="o">/</span> <span class="p">(</span><span class="n">in_max</span> <span class="o">-</span> <span class="n">in_min</span><span class="p">)</span> <span class="o">+</span> <span class="n">out_min</span><span class="p">;</span></div><div class='line' id='LC1004'><span class="p">}</span><span class="c1">//end map</span></div></pre></div>
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


    <p class="right">&copy; 2013 <span title="0.07837s from fe18.rs.github.com">GitHub</span>, Inc. All rights reserved.</p>
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

    
    
    <span id='server_response_time' data-time='0.07883' data-host='fe18'></span>
    
  </body>
</html>

