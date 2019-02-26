//require(['i18n!_core', 'underscore'], function (I18n, _) {
require(['i18nObj', 'underscore'], function (i18nObj, _) {
    I18n = i18nObj.scoped('_core');
    //var UIMask, addLogo, customHelp, customFooter, customHeader, logo, mask;
    var UIMask, addLogo, customHelp, customHeader, logo, mask;
	
	//CDA France changes to hide the combine account button and reset the message
    if($('.disambiguation_box').length) {
		console.log("Inside the merge account message");
		$(".disambiguation_box").children().first().text("Sorry, this operation cannot be performed at this time.");
		$('.disambiguation_box #merge').hide();
	}

    // Google Analytics Code
    (function (i, s, o, g, r, a, m) {
        i['GoogleAnalyticsObject'] = r; i[r] = i[r] || function () {
            (i[r].q = i[r].q || []).push(arguments)
        }, i[r].l = 1 * new Date(); a = s.createElement(o),
        m = s.getElementsByTagName(o)[0]; a.async = 1; a.src = g; m.parentNode.insertBefore(a, m)
    })(window, document, 'script', '//www.google-analytics.com/analytics.js', 'ga');

    ga('create', 'UA-62360702-1', 'auto');
    ga('send', 'pageview');

    // sanaik - Enabling on 01/12/2017 for Akamai measurements.
    // instructure - Disabling on 03/19/2018 to debug issue (CNVS-41745)
    // console.log("Appending newrelic.js for PROD");
    // var s = document.createElement("script");
    // s.type = "text/javascript";
    // s.src = "https://d2tvcrhpnl73v8.cloudfront.net/canvas-production/newrelic_prod.js";
    // document.body.appendChild(s);

    $('#primaryNavToggle').hide();

    // CHANGE favicon
    $('link[rel="Shortcut Icon"]').remove()
    $('head').append('<link href="https://d1ej7ofr54nmsd.cloudfront.net/liveaxle-theme/images/favicon.ico" rel="Shortcut Icon">')

    // Custom code for fancy IoE and CCNAS GUI
    function IoE(course) {

        pollForIoE(0);
        pagesLinkChange();
        checkInstructorHome();

        // poll to check for IoE or CCNAS specific div
        function pollForIoE(count) {
            if ($('#linktocurric').length > 0) {
                addFancyIoEUI();
            } else if (count < 10) {
                setTimeout(function () {
                    pollForIoE(++count);
                }, 200);
            }
        }
        // get path to class
        function getPath() {
            var prot = window.location.protocol;
            var host = window.location.host;
            return prot + "//" + host + "/courses/" + course;
        }
        // points the "pages" button in left nav to the "pages" page.
        function pagesLinkChange() {
            var pagesElements = document.getElementsByClassName("pages");
            for (var i in pagesElements) {
                if (pagesElements[i].href !== undefined) {
                    pagesElements[i].href = getPath() + "/pages";
                }
            }
        }
        // check to see if we need to add an "instructor home page" link to left nav
        function checkInstructorHome() {
            var showIH = false;  //flag for instructor or admin
            var env = window.ENV.current_user_roles, r;
            for (r in env) {
                if (env[r].toLowerCase() == "teacher" || env[r].toLowerCase() == "admin") {
                    showIH = true;
                    break;
                }
            }
            // if an admin or instructor then check to see if we should display the instructor home link
            if (showIH) {
                // 2015.11.16 - sanaik - added .toLowerCase() on locale - https://jira.netacad.net/jira/browse/CAE-19499
                // var locale = window.I18n.locale.toLowerCase();   //language code from canvas
                var locale = i18nObj.locale.toLowerCase();   //language code from canvas
                // check if we already have title and URL set in a cookie for this class and lang
                var cookie = getCookie("instructorhome" + course + locale);
                if (cookie !== "") {
                    var title = decodeURIComponent(cookie.split("::")[0]); // US-4126
                    var html_url = cookie.split("::")[1];
                    addInstrHomeLink(title, html_url);
                } else {
                    var instructorHomeText = {};
                    //   localized strings in array
                    instructorHomeText["en"] = [{"title":"Instructor Home","path":"instructor-home"}];
                    instructorHomeText["es"] =[{"title":"Página de inicio para el instructor","path":"pagina-de-inicio-para-el-instructor"},{"title":"Página inicio para  instructor","path":"pagina-inicio-para-instructor"},{"title":"Inicio para el instructor","path":"inicio-para-el-instructor"},{"title":"Inicio para instructores","path":"inicio-para-instructores"}];
                    instructorHomeText["fr"] = [{"title":"Accueil instructeur","path":"accueil-instructeur"},{"title":"Guide d'instructeur","path":"guide-dinstructeur"}];
                    instructorHomeText["de"] = [{"title":"Startseite für Instruktoren","path":"startseite-fur-instruktoren"},{"title":"Startseite für Instruktor/in","path":"startseite-fur-instruktor-slash-in"}];
                    instructorHomeText["it"] = [{"title":"Risorse per istruttore","path":"risorse-per-istruttore"},{"title":"Instructor Home ","path":"instructor-home"},{"title":"Pagina iniziale per l'istruttore","path":"pagina-iniziale-per-listruttore"},{"title":"Página de inicio para el instructor","path":"pagina-de-inicio-para-el-instructor"}];
                    instructorHomeText["ru"] = [{"title":"Главная страница для инструкторов","path":"glavnaia-stranitsa-dlia-instruktorov"},{"title":"Главная страница для преподавателей","path":"glavnaia-stranitsa-dlia-priepodavatieliei"},{"title":"Главная страница преподавателя","path":"glavnaia-stranitsa-priepodavatielia"}];
                    instructorHomeText["ro"] =[{"title":"Pagina Principală a Instructorului","path":"pagina-principala-a-instructorului"},{"title":"Instructor Acasă","path":"instructor-acasa"}];
                    instructorHomeText["tr"] =[{"title":"Eğitmen Ana Sayfası","path":"egitmen-ana-sayfasi"},{"title":"Eğitici Giriş Sayfası","path":"egitici-giris-sayfasi"},{"title":"Eğitmen Giriş Sayfası","path":"egitmen-giris-sayfasi"}];
                    instructorHomeText["hu"] =[{"title":"Oktatói oldal","path":"oktatoi-oldal"},{"title":"Oktató főoldal","path":"oktato-fooldal"}];
                    instructorHomeText["hi"] =[{"title":"प्रशिक्षक होम","path":"prshikssk-hom"}];
                    instructorHomeText["ko"] =[{"title":"강사 홈","path":"gangsa-hom"}];
                    instructorHomeText["ja"] =[{"title":"インストラクター ホーム","path":"insutorakuta-homu"},{"title":"インストラクタ向けホーム","path":"insutorakutaxiang-kehomu"},{"title":"インストラクターホーム","path":"insutorakutahomu"}];
                    instructorHomeText["zh-tw"] =[{"title":"教師主頁","path":"jiao-shi-zhu-ye"},{"title":"教師首頁","path":"jiao-shi-shou-ye"}];
                    instructorHomeText["zh-hans"] =[{"title":"教師主頁","path":"jiao-shi-zhu-ye"},{"title":"教師首頁","path":"jiao-shi-shou-ye"}];
                    instructorHomeText["zh-cn"] =[{"title":"教师主页","path":"jiao-shi-zhu-ye"}];
                    instructorHomeText["zh-hant"] =[{"title":"教师主页","path":"jiao-shi-zhu-ye"}];
                    instructorHomeText["zh"] =[{"title":"教师主页","path":"jiao-shi-zhu-ye"}];
                    instructorHomeText["pl"] =[{"title":"Strona główna instruktora","path":"strona-glowna-instruktora"}];
                    instructorHomeText["pt-br"] =[{"title":"Página inicial do instrutor","path":"pagina-inicial-do-instrutor"},{"title":"Início para o instrutor","path":"inicio-para-o-instrutor"}, {"title":"Início para o instructor","path":"inicio-para-o-instructor"}];
                    instructorHomeText["pt"] =[{"title":"Página inicial do instrutor","path":"pagina-inicial-do-instrutor"},{"title":"Início para o instrutor","path":"inicio-para-o-instrutor"}, {"title":"Início para o instructor","path":"inicio-para-o-instructor"}];
                    instructorHomeText["el"] =[{"title":"Αρχική Εκπαιδευτής","path":"arkhike-ekpaideutes"}];
                    instructorHomeText["hr"] =[{"title":"Početna stranica za predavače","path":"pocetna-stranica-za-predavace"}];
                    instructorHomeText["iw"] =[{"title":"דף הבית למורה", "path":"dp-hbyt-lmvrh"}];
                    instructorHomeText["he"] =[{"title":"דף הבית למורה", "path":"dp-hbyt-lmvrh"},{"title":"Instructor Home", "path":"instructor-home"}];
                    instructorHomeText["ua"] =[{"title":"Головна сторінка інструктора", "path":"golovna-storinka-instruktora"}];
                    instructorHomeText["ka"] =[{"title":"ინსტრუქტორის მთავარი გვერდი","path":"instruk`toris-mt`avari-gverdi"}];
					instructorHomeText["ar"] =[{"title":"الصفحة الرئيسية للمعلم","path":"lsfh@-lry'ysy@-llm%60lm"},{"title":"لصفحة الرئيسية للمعلم","path":"lsfh-at-lryysy-at-llm%60lm"},{"title":" الصفحة الرئيسية للمعلّم","path":" lsfh-at-lryysy-at-lm%60lwm"}];
					instructorHomeText["kk"] = [{"title":"Нұсқаушы Басты беті","path":" nuskaushy-basty-bieti"}];
					instructorHomeText["nl"] = [{"title":"Instructor Homepagina","path":" Instructor Homepagina"}];
                    // get an array of all pages in the class
					var foundTitle = false;
                    $.get("/api/v1/courses/" + course + "/pages?per_page=100", function (data) {
                        for (var jj in instructorHomeText[locale]) {
                            // for each localized string for the users language
                            for (var kk in data) {
                                // go through all of the pages in the class
                                if (instructorHomeText[locale][jj].title.split(" ").join("") === data[kk].title.split(" ").join("") && data[kk].title !== "undefined") {
                                    // our localized string matches a page in the class so create the instructor home link
                                    addInstrHomeLink(data[kk].title, data[kk].html_url);
                                    setCookie("instructorhome" + course + locale, encodeURIComponent(data[kk].title) + "::" + data[kk].html_url, 14); // US-4126
                                    foundTitle = true;
									break;
                                }
                            }
                        }
						if(!foundTitle){
                            // go through all of the pages in the class and look for all lang titles
							for(var ii in instructorHomeText){
								for(var jj in instructorHomeText[ii]){
									for (var kk in data) {
										if (instructorHomeText[ii][jj].title.split(" ").join("") === data[kk].title.split(" ").join("") && data[kk].title !== "undefined"){
											addInstrHomeLink(data[kk].title, data[kk].html_url);
											setCookie("instructorhome" + course + locale, encodeURIComponent(data[kk].title) + "::" + data[kk].html_url, 14); 
											foundTitle = true;
											break;
										}
									}
									if(foundTitle) break;
								}
								if(foundTitle) break;
							}        
                        }
                    });
                }
            }
        }

        // set cookie -  used so the Instructor Home check doesn't have to run every page load.
        function setCookie(cname, cvalue, exdays) {
            var d = new Date();
            d.setTime(d.getTime() + (exdays * 24 * 60 * 60 * 1000));
            var expires = "expires=" + d.toUTCString();
            document.cookie = cname + "=" + cvalue + "; " + expires;
        }

        function getCookie(cname) {
            var name = cname + "=";
            var ca = document.cookie.split(';');
            for (var i = 0; i < ca.length; i++) {
                var c = ca[i];
                while (c.charAt(0) == ' ') c = c.substring(1);
                if (c.indexOf(name) === 0) return c.substring(name.length, c.length);
            }
            return "";
        }

        function addInstrHomeLink(title, pageUrl) {
            var nav = document.getElementById("section-tabs");
            if (nav) {
                var li = document.createElement("li");
                li.id = "ihLink";
                li.setAttribute("class", "section");
                var a = document.createElement("a");
                a.appendChild(document.createTextNode(title));
                a.setAttribute("href", pageUrl);
                li.appendChild(a);
		// Append at the end of the list
                nav.insertBefore(li, null);
            }
        }

        //  if the div is present then we add some custom UI to the page
        function addFancyIoEUI() {
            if ($('#linktocurric').length > 0) {
                var containerHeight = ($("#main").height() - 57);
                var courseID = "";
                if ($('#coursePre').length > 0) {
                    courseID = document.getElementById("coursePre").innerHTML;
                    document.getElementById("coursePre").style.visibility = "hidden";
                } else if ($('#ConnData').length > 0) {
                    courseID = "ConnData";
                } else if ($('#CCNAS_course').length > 0) {
                    courseID = "CCNAS";
                } else if ($('#ioe11KO').length > 0) {
                    courseID = "IoE11KO";
                } else if ($('#ioe11').length > 0) {
                    courseID = "IoE11";
                } else if ($('#ioe12').length > 0) {
                    courseID = "IoE12";
                } else if ($('#ConnDataSupplemental').length > 0) {
                    courseID = "ConnDataSupplemental";
                } else {
                    courseID = "IoE";
                }
                if ($('#courseLang').length > 0) {
                    courseID += "/" + document.getElementById("courseLang").innerHTML;
                    document.getElementById("courseLang").style.visibility = "hidden";
                }

                $('#launchpagebg').css("background-image", "url(https://static-course-assets.s3.amazonaws.com/" + courseID + "/launch/launchbg.jpg)");
                $('#launchpagebg').css("min-width", "700px");
                $('#launchpagebg').height(590);
                $('#launchContainer a').css("color", "#fff");
                $('#launchContainer').css("color", "#fff");
                $('#launchContainer').css("font-family", "Arial, Helvetica, sans-serif");
                $('#launchContainer').css("font-size", "large");
                $('#launchContainer a').css("text-decoration", "none");
                $('#launchContainer').css("position", "absolute");
                $('#launchContainer').css("top", "125px");
                $('#launchContainer').css("left", "50px");
                $('#launchContainer').css("width", "600");
                $('#launchContainer').css("height", "300");

                $('#buttonBox').width('525px');
                $('#buttonBox').height('255px');
                $('#buttonBox').css('position', "absolute");
                $('#buttonBox').css('top', '10px');
                $('#buttonBox').css('left', '10px');
                $('#buttonBox').css('border', "2px solid");
                $('#buttonBox').css('padding-left', '25px');
                $('#buttonBox').css('padding-right', '25px');
                $('#buttonBox').css('padding-top', '25px');
                $('#buttonBox').css('padding-bottom', '25px');

                $('#launchTitle').css("padding-bottom", "20px");
                //$('#launchTitle').css("text-align","center");
                $('#launchTitle').css("padding-left", "-50px");
                $('#launchTitle').width("100%");

                $('#boxbg').css("background-color", "#333");
                $('#boxbg').width('600px');
                $('#boxbg').height('330px');
                $('#boxbg').css('opacity', '.7');
                $('#boxbg').css('filter', ' alpha(opacity = 70)');
                $('#boxbg').css("border", "medium");
                $('#boxbg').css('border-color', "#000");

                //    launch the course
                var coursePath = "<a href='https://static-course-assets.s3.amazonaws.com/" + courseID + "/index.html?r=https://";

                coursePath += (window.ENV.files_domain) + "/courses/";
                coursePath += course;
                console.log("check for presence of class " + $('#linktocurric').attr('class'));
                if (typeof ($('#linktocurric').attr('class')) !== "undefined") {

                    console.log("   found loadpage");
                    coursePath += "#" + $('#linktocurric').attr('class');
                }
                coursePath += "' id='launchlink'>";
                document.getElementById('linktocurric').innerHTML = coursePath + document.getElementById('linktocurric').innerHTML + "</a>";
                $('#launchlink').css("text-decoration", "none");
                $('#launchlink').css("color", "#ffffff");
                $('#launchlink').on({ 'focus': function () { $('#launchbtn').attr('src', 'https://static-course-assets.s3.amazonaws.com/' + courseID + '/launch/btn_1_over.png'); } });
                $('#launchlink').on({ 'blur': function () { $('#launchbtn').attr('src', 'https://static-course-assets.s3.amazonaws.com/' + courseID + '/launch/btn_1_normal.png'); } });
                $('#linktocurric').on({
                    'mouseover': function () {
                        $('#launchbtn').attr('src', 'https://static-course-assets.s3.amazonaws.com/' + courseID + '/launch/btn_1_over.png');
                    },
                    'mouseout': function () {
                        $('#launchbtn').attr('src', 'https://static-course-assets.s3.amazonaws.com/' + courseID + '/launch/btn_1_normal.png');
                    }
                });
                if ($('#linktohelp').length > 0) {
                    //  button to load "first time user" info page in canvas
                    $('#linktohelp').click(function (event) {
                        var helpPath = "/courses/";
                        helpPath += course;
                        helpPath += "/wiki/first-time-in-this-course";
                        top.location.href = helpPath;
                    });
                    $('#linktohelp > a')[0].setAttribute('id', 'helplink');
                    $('#helplink').on({
                        'focus': function () {
                            $('#helpbtn').attr('src', 'https://static-course-assets.s3.amazonaws.com/' + courseID + '/launch/btn_2_over.png');
                        },
                        'mouseover': function () {
                            $('#helpbtn').attr('src', 'https://static-course-assets.s3.amazonaws.com/' + courseID + '/launch/btn_2_over.png');
                        },
                        'blur': function () {
                            $('#helpbtn').attr('src', 'https://static-course-assets.s3.amazonaws.com/' + courseID + '/launch/btn_2_normal.png');
                        },
                        'mouseout': function () {
                            $('#helpbtn').attr('src', 'https://static-course-assets.s3.amazonaws.com/' + courseID + '/launch/btn_2_normal.png');
                        }
                    });
                }
            }
        }
    }
    // END FANCY INTERFACE CODE

    // ### Domain-Specific Customizations

    // Translations for Home link title
    //var locale = window.I18n.locale;
    var locale = i18nObj.locale;

        if(locale == 'es'){
        homeLinkTitleText = 'Mi NetAcad';
      } else if(locale == 'fr'){
        homeLinkTitleText = 'Mon NetAcad';
      } else if(locale == 'pt'){
        homeLinkTitleText = 'Minha NetAcad';
      } else if(locale == 'ru'){
        homeLinkTitleText = 'Моя Академия';
      } else if(locale == 'ar'){
        homeLinkTitleText = 'NetAcad الخاصة بي'
      } else if(locale == 'zh'){
        homeLinkTitleText = '我的 NetAcad';
      } else if(locale == 'zh-Hans'){
        homeLinkTitleText = '我的 NetAcad';
      } else if(locale == 'zh-Hant'){
        homeLinkTitleText = '我的 NetAcad';
      } else if(locale == 'nl'){
        homeLinkTitleText = 'Mijn NetAcad';
      } else if(locale == 'de'){
        homeLinkTitleText = 'Mein NetAcad';
      } else if(locale == 'ja'){
        homeLinkTitleText = 'マイ NetAcad';
      } else if(locale == 'pl'){
        homeLinkTitleText = 'Moja NetAcad';
      } else{
          homeLinkTitleText = 'My NetAcad';
      }
        
        // Default customizations. Overrides in customOverrides object below
        var franceDefaultCustoms = {
            liferayUrl: 'https://cisco-colleges.fr',
            liferayHome: '/group/landing',

            // Initialize customizations (manipulates DOM!)
            init: function () {
                this.franceCustomHeader().init();
                this.franceCustomHelp().init();
                //this.customFooter().init();
            },

            // Customize header to use custom liferay URLs based on domain
            franceCustomHeader: function () {
                var _this = this;
                return {
                    init: function () {
                        var $header = $('#menu');
                        $header.append(this.homeLink());

                        return $header.find('a[href*="profile"]:first').attr('href', this.settings);
                    },
                    settings: _this.liferayUrl + _this.liferayHome + "?p_p_id=netacaduserprofile_WAR_netacaduserprofileportlet&p_p_lifecycle=0&p_p_state=maximized&p_p_mode=view&_netacaduserprofile_WAR_netacaduserprofileportlet_jspPage=%2Fview.jsp&_netacaduserprofile_WAR_netacaduserprofileportlet_privateLayout=true&_netacaduserprofile_WAR_netacaduserprofileportlet_fromtheme=true&_netacaduserprofile_WAR_netacaduserprofileportlet_fromthemeRedirect=%2Fgroup%2Flanding%3Fp_p_id%3Dnetacaduserprofile_WAR_netacaduserprofileportlet",
                    homeLinkTemplate: _.template('<li id="customHomeBtn" class="menu-item  ic-app-header__menu-list-item"><a class="ic-app-header__menu-list-link" href="<%= domain %><%= path %>"><div class="menu-item-icon-container" aria-hidden="true"><img src="https://s3.amazonaws.com/web_assets/canvas-test/Home_2-01.png" alt="'+homeLinkTitleText+'"/></div><div class="menu-item__text"><%= title %></div></a></li>'),
                    homeLinkTitle: homeLinkTitleText,
                    homeLink: function () {
                        return this.homeLinkTemplate({
                            domain: _this.liferayUrl,
                            path: _this.liferayHome,
                            title: this.homeLinkTitle
                        });
                    }
                };
            },

            // Customize help menu to match Liferay's help menu
            franceCustomHelp: function () {
                var _this = this;
                return {
                    init: function () {
                        // Assemble link HTML
                        var links = this.parseLinks(this.links, _.template("<li>" +
                          "<a href=\"<%= domain %><%= url %>\">" +
                            "<span class=\"text\"><%= title %></span></a><br>" +
                            "<span class=\"subtext\"><%= description %></span></li><br>"));

                        var _this = this;
                        this.onHelpDialog(function (dialog) {
                            $(function () {
                                dialog.children().not(dialog.find('a[href=#teacher_feedback]').parent().parent()).remove();
                                _this.addLinks(links, dialog);
                                _this.parseTicketForm();
                            });
                        });
                    },

                    // leave domain blank to keep link url relative to Canvas
                    // find I18n paths here: https://github.com/instructure/canvas-lms/blob/stable/config/locales/en.yml
                    links: [
                      // roles: array of roles that are allowed to see menu item
                      // domain: https://domain-of-link.com (use _this.liferayUrl for all things liferay)
                      // url: /the/rest/of/the/url
                      {
                          roles: ['admin', 'teacher', 'student'],
                          domain: 'https://www.cisco-colleges.fr',
                          url: '/group/landing/faq',
                          title: I18n.t('#support.help_menu.networking_academy_faqs', 'Networking Academy FAQs'),
                          description: I18n.t('#support.help_menu.networking_academy_description', 'View Cisco answers to the most commonly asked questions.')
                      },
                      
                      {//Jer-Added Footer Links to Custom Help Menu
                          roles: ['admin', 'teacher', 'student'],
                          domain: 'https://cisco-colleges.fr',
                          url: '/web/about-us/terms-and-conditions/',
                          title: I18n.t('Terms and Conditions'),
                          description: I18n.t('Terms and Conditions for use of Cisco Networking Academy Sites and Services.')
                      },
                      {
                          roles: ['admin', 'teacher', 'student'],
                          domain: 'https://www.cisco.com',
                          url: '/web/siteassets/legal/privacy.html',
                          title: I18n.t('Privacy Statement'),
                          description: I18n.t('Cisco Online Privacy Statement Summary.')
                      },
                      {
                          roles: ['admin', 'teacher', 'student'],
                          domain: 'https://www.cisco.com',
                          url: '/web/siteassets/legal/privacy_full.html#cookies',
                          title: I18n.t('Cookie Policy'),
                          description: I18n.t('Use of Cookies and other Web Technologies.')
                      },
                      {
                          roles: ['admin', 'teacher', 'student'],
                          domain: 'https://www.cisco.com',
                          url: '/web/siteassets/legal/trademark.html',
                          title: I18n.t('Trademarks'),
                          description: I18n.t('List of Cisco trademarks and registered trademarks in the US and certain other countries.')
                      },
                    ],

                    addLinks: function (links, element) {
                        var userRoles = ENV && ENV.current_user_roles;
                        if (_.isArray(userRoles)) {
                            _(links).each(function (link) {
                                // Adds link iff current user is permitted (defined in customHelp.links.roles)
                                // If role array is not provided in link object, the link will be added for all users
                                var currentUserIsAuthorized = _(userRoles).any(function (role) {
                                    return !link.roles || !!~link.roles.indexOf(role);
                                });

                                if (currentUserIsAuthorized) {
                                    element.append(link.url);
                                }
                            });
                        }
                    },

                    // div#help-dialog-options is passed to callback
                    onHelpDialog: function (callback) {
                        // register event listener - wait for help to be clicked
                        $('#global_nav_help_link').on('click', function () {
                            // Wait for help dialog to appear
                            // Tweak here to adjust responsiveness
                            var attempt = 0;
                            var attempt_max = 20;
                            var poll_time = 500;
                            function poll(cb) {
                                setTimeout(function () {
                                    attempt += 1;
                                    var dialog = $('#help_tray ul');
                                    if (!!dialog.length)
                                        cb(dialog);
                                    else if (attempt < attempt_max)
                                        poll(cb);
                                }, poll_time);
                            }
                            poll(callback);
                        });
                    },

                    // Parses templates in main template and link URLs
                    // Modifies objects in customHelp.links!!
                    parseLinks: function (links, template) {
                        return _.map(links, function (link) {
                            // parse template variables in link.url with appropriate liferayUrl
                            link.url = _.template(link.url)({
                                domain: _this.liferayUrl
                            });

                            // parse html <li> element template
                            link.url = template(_.extend({
                                domain: _this.liferayUrl
                            }, link));

                            return link;
                        });
                    },

                    parseTicketForm: function () {
                        var form = $('#create_ticket');
                        var toRemove = form.find('label[for=severity], select#severity, .ui-state-highlight');
                        if (toRemove.length > 0) {
                            toRemove.remove();
                            return form.append($('<input />', {
                                name: 'error[user_perceived_severity]',
                                type: 'hidden',
                                value: 'just_a_comment'
                            }));
                        } else {
                            return form.find('input[name="error[user_perceived_severity]"]').val('just_a_comment');
                        }
                    }
                };
            },

            //customFooter: function() {
            //  var _this = this;
            //  return {
            //    tpl: "<div class=\"footer-container\">\n  <ul class=\"footer-nav pull-left\">\n    <li><a href=\"{{domain}}/web/about-us/terms-and-conditions/\">Terms and Conditions</a></li>\n    <li>|</li>\n    <li><a href=\"http://www.cisco.com/web/siteassets/legal/privacy.html\">Privacy Statement</a></li>\n    <li>|</li>\n    <li><a href=\"http://www.cisco.com/web/siteassets/legal/privacy_full.html#cookies\">Cookie Policy</a></li>\n    <li>|</li>\n    <li><a href=\"http://www.cisco.com/web/siteassets/legal/trademark.html\">Trademarks</a></li>\n  </ul>\n\n  <div style=\"clear: both;\"></div>\n</div>",
            //    init: function() {
            //     var footer;
            //      footer = $('#footer');
            //      if (window.location.pathname !== '/login') {
            //        return footer.html(this.tpl.replace('{{domain}}', _this.liferayUrl)).appendTo('body');
            //      }
            //    }
            //  };
            //},
        };

    // Default customizations. Overrides in customOverrides object below
    var defaultCustoms = {
        liferayUrl: 'https://www.netacad.com',
        liferayHome: '/group/landing',

        // Initialize customizations (manipulates DOM!)
        init: function () {
            this.customHeader().init();
            this.customHelp().init();
            //this.customFooter().init();
        },

        // Customize header to use custom liferay URLs based on domain
        customHeader: function () {
            var _this = this;
            return {
                init: function () {
                    var $header = $('#menu');
                    $header.append(this.homeLink());

                    return $header.find('a[href*="profile"]:first').attr('href', this.settings);
                },
                settings: _this.liferayUrl + _this.liferayHome + "?p_p_id=netacaduserprofile_WAR_netacaduserprofileportlet&p_p_lifecycle=0&p_p_state=maximized&p_p_mode=view&_netacaduserprofile_WAR_netacaduserprofileportlet_jspPage=%2Fview.jsp&_netacaduserprofile_WAR_netacaduserprofileportlet_privateLayout=true&_netacaduserprofile_WAR_netacaduserprofileportlet_fromtheme=true&_netacaduserprofile_WAR_netacaduserprofileportlet_fromthemeRedirect=%2Fgroup%2Flanding%3Fp_p_id%3Dnetacaduserprofile_WAR_netacaduserprofileportlet",
                homeLinkTemplate: _.template('<li id="customHomeBtn" class="menu-item  ic-app-header__menu-list-item"><a class="ic-app-header__menu-list-link" href="<%= domain %><%= path %>"><div class="menu-item-icon-container" aria-hidden="true"><img src="https://s3.amazonaws.com/web_assets/canvas-test/Home_2-01.png" alt="'+homeLinkTitleText+'"/></div><div class="menu-item__text"><%= title %></div></a></li>'),
                homeLinkTitle: homeLinkTitleText,
                homeLink: function () {
                    return this.homeLinkTemplate({
                        domain: _this.liferayUrl,
                        path: _this.liferayHome,
                        title: this.homeLinkTitle
                    });
                }
            };
        },

        // Customize help menu to match Liferay's help menu
        customHelp: function () {
            var _this = this;
            return {
                init: function () {
                    // Assemble link HTML
                    var links = this.parseLinks(this.links, _.template("<li>" +
                      "<a href=\"<%= domain %><%= url %>\">" +
                        "<span class=\"text\"><%= title %></span></a><br>" +
                        "<span class=\"subtext\"><%= description %></span></li><br>"));

                    var _this = this;
                    this.onHelpDialog(function (dialog) {
                        $(function () {
                            dialog.children().not(dialog.find('a[href=#teacher_feedback]').parent().parent()).remove();
                            _this.addLinks(links, dialog);
                            _this.parseTicketForm();
                        });
                    });
                },

                // leave domain blank to keep link url relative to Canvas
                // find I18n paths here: https://github.com/instructure/canvas-lms/blob/stable/config/locales/en.yml
                links: [
                  // roles: array of roles that are allowed to see menu item
                  // domain: https://domain-of-link.com (use _this.liferayUrl for all things liferay)
                  // url: /the/rest/of/the/url
                  {
                      roles: ['admin', 'teacher'],
                      domain: _this.liferayUrl,
                      url: '/group/communities/community-home',
                      title: I18n.t('#support.help_menu.community_support_forums', 'Community Support Forums'),
                      description: I18n.t('#support.help_menu.community_support_description', 'Interact with and get assistance from your peers.')
                  },
                  {
                      roles: ['admin', 'teacher', 'student'],
                      domain: 'https://www.netacad.com',
                      url: '/group/landing/faq',
                      title: I18n.t('#support.help_menu.networking_academy_faqs', 'Networking Academy FAQs'),
                      description: I18n.t('#support.help_menu.networking_academy_description', 'View Cisco answers to the most commonly asked questions.')
                  },
                  {
                      roles: ['admin', 'teacher'],
                      //domain: '',
                      //url: '#create_ticket',
                      domain: 'https://www.netacad.com',
                      url: '/group/support/canvas-support',
                      //title: I18n.t('#support.help_menu.global_support_desk', 'Global Support Desk'),
					  title: 'NetAcad Support',
                      description: I18n.t('#support.help_menu.global_support_desk_description', 'Our ASCs are your first line of support, and can connect you with our Global Support Desk for issues that require additional assistance.')
                  },
                  /*{
                      roles: ['admin', 'teacher'],
                      domain: _this.liferayUrl,
                      url: '/group/support/support-desk#_salesforcecase_WAR_salesforcecaseportlet_Submit',
                      title: I18n.t('#support.help_menu.support_desk_livechat', 'Support Desk Live Chat'),
                      description: I18n.t('#support.help_menu.community_support_description', 'Our ASCs are your first line of support, and can connect you with our Global Support Desk for issues that require additional assistance.')
                  },*/
                  {
                      roles: ['student'],
					  domain: 'https://www.netacad.com',
                      url: '/group/support/canvas-support',
                      title: 'NetAcad Support - Student',
                      description: 'Please visit our Networking Academy Facebook page for community support or contact your instructor.'
                  },
                  /*{//Using original functionality now due to react js changes
                      roles: ['student'],
                      domain: '',
                      url: '#teacher_feedback',
                      title: I18n.t('#help_dialog.instructor_question', 'Ask Your Instructor a Question'),
                      description: I18n.t('#help_dialog.instructor_question_sub', 'Questions are submitted to your instructor')
                  },*/
                  {//Jer-Added Footer Links to Custom Help Menu
                      roles: ['admin', 'teacher', 'student'],
                      domain: 'https://www.netacad.com',
                      url: '/web/about-us/terms-and-conditions/',
                      title: I18n.t('Terms and Conditions'),
                      description: I18n.t('Terms and Conditions for use of Cisco Networking Academy Sites and Services.')
                  },
                  {
                      roles: ['admin', 'teacher', 'student'],
                      domain: 'https://www.cisco.com',
                      url: '/web/siteassets/legal/privacy.html',
                      title: I18n.t('Privacy Statement'),
                      description: I18n.t('Cisco Online Privacy Statement Summary.')
                  },
                  {
                      roles: ['admin', 'teacher', 'student'],
                      domain: 'https://www.cisco.com',
                      url: '/web/siteassets/legal/privacy_full.html#cookies',
                      title: I18n.t('Cookie Policy'),
                      description: I18n.t('Use of Cookies and other Web Technologies.')
                  },
                  {
                      roles: ['admin', 'teacher', 'student'],
                      domain: 'https://www.cisco.com',
                      url: '/web/siteassets/legal/trademark.html',
                      title: I18n.t('Trademarks'),
                      description: I18n.t('List of Cisco trademarks and registered trademarks in the US and certain other countries.')
                  },
                ],

                addLinks: function (links, element) {
                    var userRoles = ENV && ENV.current_user_roles;
                    if (_.isArray(userRoles)) {
                        _(links).each(function (link) {
                            // Adds link iff current user is permitted (defined in customHelp.links.roles)
                            // If role array is not provided in link object, the link will be added for all users
                            var currentUserIsAuthorized = _(userRoles).any(function (role) {
                                return !link.roles || !!~link.roles.indexOf(role);
                            });

                            if (currentUserIsAuthorized) {
                                element.append(link.url);
                            }
                        });
                    }
                },

                // div#help-dialog-options is passed to callback
                onHelpDialog: function (callback) {
                    // register event listener - wait for help to be clicked
                    $('#global_nav_help_link').on('click', function () {
                        // Wait for help dialog to appear
                        // Tweak here to adjust responsiveness
                        var attempt = 0;
                        var attempt_max = 20;
                        var poll_time = 500;
                        function poll(cb) {
                            setTimeout(function () {
                                attempt += 1;
                                var dialog = $('#help_tray ul');
                                if (!!dialog.length)
                                    cb(dialog);
                                else if (attempt < attempt_max)
                                    poll(cb);
                            }, poll_time);
                        }
                        poll(callback);
                    });
                },

                // Parses templates in main template and link URLs
                // Modifies objects in customHelp.links!!
                parseLinks: function (links, template) {
                    return _.map(links, function (link) {
                        // parse template variables in link.url with appropriate liferayUrl
                        link.url = _.template(link.url)({
                            domain: _this.liferayUrl
                        });

                        // parse html <li> element template
                        link.url = template(_.extend({
                            domain: _this.liferayUrl
                        }, link));

                        return link;
                    });
                },

                parseTicketForm: function () {
                    var form = $('#create_ticket');
                    var toRemove = form.find('label[for=severity], select#severity, .ui-state-highlight');
                    if (toRemove.length > 0) {
                        toRemove.remove();
                        return form.append($('<input />', {
                            name: 'error[user_perceived_severity]',
                            type: 'hidden',
                            value: 'just_a_comment'
                        }));
                    } else {
                        return form.find('input[name="error[user_perceived_severity]"]').val('just_a_comment');
                    }
                }
            };
        },

        //customFooter: function() {
        //  var _this = this;
        //  return {
        //    tpl: "<div class=\"footer-container\">\n  <ul class=\"footer-nav pull-left\">\n    <li><a href=\"{{domain}}/web/about-us/terms-and-conditions/\">Terms and Conditions</a></li>\n    <li>|</li>\n    <li><a href=\"http://www.cisco.com/web/siteassets/legal/privacy.html\">Privacy Statement</a></li>\n    <li>|</li>\n    <li><a href=\"http://www.cisco.com/web/siteassets/legal/privacy_full.html#cookies\">Cookie Policy</a></li>\n    <li>|</li>\n    <li><a href=\"http://www.cisco.com/web/siteassets/legal/trademark.html\">Trademarks</a></li>\n  </ul>\n\n  <div style=\"clear: both;\"></div>\n</div>",
        //    init: function() {
        //     var footer;
        //      footer = $('#footer');
        //      if (window.location.pathname !== '/login') {
        //        return footer.html(this.tpl.replace('{{domain}}', _this.liferayUrl)).appendTo('body');
        //      }
        //    }
        //  };
        //},
    };

    // Domain-Specific overrides to above customizations
    // Multiple domains can be listed with commas
    // NOTE: if two domains with names that contain each other need separate customization,
    //        define the more specific name BEFORE the less specific name.
    //        processCustoms() uses window.location.hostname.indexOf() to determine which customization to use
    //        thus, the first match will be used.
    //        Example: jaeuropecanvas-stage must be defined before jaeuropecanvas
    var customOverrides = {
        /* Example override:
         * 'a_canvas_domain': {
         *      liferayUrl: 'https://custom_liferay_url.com',
         *      // overriding init function for fine-grain control
         *      init: function() {
         *          var header = this.customHeader(); // get a customHeader object
         *          header.homeLinkTitle: 'CustomAcademy'; // modify properties of the object
         *          header.init(); // init the object when finished
         *          this.customFooter().init(); // don't forget to init the other wanted components
         *          // no custom help init because we want the Canvas default
         *      }
         *  }
         *
         */

        'lms-ciscoskillzone.netacad.com': {
            liferayUrl: 'https://skillzone.cisconetspace.com',
            liferayHome: '/#/experiences',
            init: function () {
                var header = this.customHeader();
                header.homeLinkTitle = 'My Skillzone';
                header.init();
            }
        },

        'gghhlearn.cisconetspace.com': {
            liferayUrl: 'https://gghhconnect.cisconetspace.com',
            liferayHome: '/canvas',
            init: function () {
                var header = this.customHeader();
                header.homeLinkTitle = 'GGHH Home';
                header.settings = '/profile/settings';
                header.init();
            }
        },

        'stellaapp.canvas-dev.cisco': {
            liferayUrl: 'http://dev-stellaapp.netspaceapp.com',
            liferayHome: '/#/dashboard',
            init: function () {
                var header = this.customHeader();
                header.homeLinkTitle = 'Home';
                header.init();
            }
        },

        'directpilot-dev.canvas-dev.cisco': {
            liferayUrl: 'https://directpilot-dev.netspaceapp.com',
            liferayHome: '/#/my-courses',
            init: function () {
                var header = this.customHeader();
                header.homeLinkTitle = 'Home';
                header.init();
            }
        },

        'canvasprod': {
            liferayUrl: 'https://liferayprod.netacadtrial.com'
        },
        //'cisco.instructure': {
        //  liferayUrl: 'https://liferay-test.netacad.com'
        //},

        'netacadtrial': {
            liferayUrl: 'https://netacadtrial.com',
            liferayHome: '/group/support'
        },

        'netacad': {
            liferayUrl: 'https://www.netacad.com'
        },

        'jaeuropecanvas-stage': {
            liferayUrl: 'https://jaeurope-stage.cisconetspace.com/user',
            liferayHome: '',
            init: function () {
                var header = this.customHeader();
                header.settings = '/profile/settings';
                header.init();
                //this.customFooter(); //.init();
            }
        },

        'jaeuropecanvas': {
            liferayUrl: 'https://jaeurope.cisconetspace.com/user',
            liferayHome: '',
            init: function () {
                var header = this.customHeader();
                header.settings = '/profile/settings';
                header.init();
                //this.customFooter(); //.init();
            }
        },

        'lmstest-gghh.canvas.cisco.instructure.com': {
            liferayUrl: 'https://gghh-test.cisconetspace.com',
            liferayHome: '/canvas',
            init: function () {
                var header = this.customHeader();
                header.homeLinkTitle = "GGHH Home";
                header.settings = 'profile/settings';
                header.init();
            }
        },

        'learn-test.ciscoskillzone.cisco.instructure.com': {
            liferayUrl: 'https://test.ciscoskillzone.com',
            liferayHome: '/#/experiences',
            init: function () {
                var header = this.customHeader();
                header.homeLinkTitle = 'My Skillzone';
                header.init();
            }
        }

    };

    function processCustoms() {
        //var hostname = window.location.hostname;
		var hostname = $.cookie('liferay-referrer');
			
        var result = defaultCustoms;
		if(hostname.indexOf('colleges.fr') >= 0) {
			result = franceDefaultCustoms;
		}
			
        _(customOverrides).any(function (data, domains) {
            return _(domains.split(',')).any(function (domain) {
                if (!!~hostname.indexOf(domain)) {
                    result = _.extend(defaultCustoms, customOverrides[domains]);
                    return true;
                }
            });
        });
                
        return result;
    }

    // ### UI Masks - Modifies Canvas UI

    UIMask = (function () {
        function UIMask() { }

        UIMask.prototype.functions = [];

        UIMask.prototype.hideUI = function () {
            var fn, _i, _len, _ref, _results;
            _ref = this.functions;
            _results = [];
            for (_i = 0, _len = _ref.length; _i < _len; _i++) {
                fn = _ref[_i];
                if (!fn[2] && window.location.href.match(/site[_\-]?admin/)) {
                    continue;
                }
                if (this.onPage(fn[0])) {
                    _results.push(fn[1].apply(this));
                }
            }
            return _results;
        };

        // desc      - description of mask
        // pages     - array of regex to match against current URL;
        //             determines where to apply mask
        // fn        - mask function
        // canBypass - will fn be executed if window.location.href.match(/site[_\-]?admin/) ?
        UIMask.prototype.add = function (desc, pages, fn, canBypass) {
            return this.functions.push([pages, fn, canBypass]);
        };

        UIMask.prototype.onPage = function (pages) {
            var page, _i, _len;
            for (_i = 0, _len = pages.length; _i < _len; _i++) {
                page = pages[_i];
                if (window.location.pathname.match(page)) {
                    return true;
                }
            }
        };

        UIMask.prototype.afterLoad = function (selector, fn) {
            var callback;
            callback = {
                selector: selector,
                fn: fn,
                execute: function () {
                    var elements;
                    elements = $(this.selector);
                    if (elements.length > 0) {
                        return this.fn(elements);
                    } else {
                        return setTimeout(this.execute, 50);
                    }
                }
            };
            callback.execute = jQuery.proxy(callback.execute, callback);
            return callback.execute();
        };

        return UIMask;
    })();

    mask = new UIMask();

    var isAdminOrTeacher = false;  //flag for Teacher or admin
    var env = window.ENV.current_user_roles, r;
    for (r in env) {
        if (env[r].toLowerCase() == "teacher" || env[r].toLowerCase() == "admin") {
            isAdminOrTeacher = true;
            break;
        }
    }

    // sanaik - 2015.10.25 -- Added as per request from Jeremiah
    // With the 9.19 canvas upgrade, a new menu item appeared on all root accounts.  Bill would like to hide this menu item.
    // Spencer wrote this javascript to add to the global cisco javascript override file so that it is hidden:
    mask.add('Developer Keys menu', [/accounts\/(\d+~)?\d+\/?/], function () {
        return $('li.section .developer_keys').parent().remove();
    }, true);

    /*mask.add('Add students and Add TAs in Course Wizard', [/courses\/(\d+~)?\d+$/], function () {
        var hideLink, link, links, wizard, _i, _len, _results;
        wizard = $('.ic-wizard-box__nav');
        links = ['#wizard_add_students', '#wizard_add_tas'];
        hideLink = function (link) {
            var el_to_hide;
            if ((el_to_hide = wizard.find(link)).length > 0) {
                return el_to_hide.remove();
            } else {
                return setTimeout(function () {
                    return hideLink(link);
                }, 100);
            }
        };
        _results = [];
        for (_i = 0, _len = links.length; _i < _len; _i++) {
            link = links[_i];
            _results.push(hideLink(link));
        }
        return _results;
    });*/

    mask.add('Add user(s) buttons', [/courses\/(\d+~)?\d+\/(settings|details)$/, /accounts\/(\d+~)?\d+(\/users)?$/, /accounts\/(\d+~)?\d+\/settings$/, /accounts\/(\d+~)?\d+\/courses\\?/], function () {
        if (!window.location.href.match(/gghhlearn.cisconetspace.com/) || !isAdminOrTeacher) {
            return $('a.add_user_link, a.add_users_link').remove();
        }
    });

    mask.add('Users profile page', [/users\/(\d+~)?\d+$/], function () {
        var profile_links;
        profile_links = $('table.profile_table td.links');
        profile_links.find('.edit_user_link').remove();
        profile_links.find(".merge_user_link").remove();
        if (profile_links.length) {
            profile_links.html(profile_links.html().replace(/\s+\|/g, ''));
        }
        $('#login_information').remove();
        return $('.unenroll_link').remove();
    });

    mask.add('Course settings sections tab', [/courses\/(\d+~)?\d+\/(settings|details)$/], function () {
        $('#sections_tab').remove();
        return $('#tab-sections').remove();
    });

    mask.add('Auth and sub-accounts links in left navigation', [/accounts\/(\d+~)?\d+/], function () {
        return $('#section-tabs').find('a.authentication, a.sub_accounts, a.terms').parent().remove();
    });

    mask.add('Add a course button', [/accounts\/(\d+~)?\d+$/, /accounts\/(\d+~)?\d+\/settings$/, /accounts\/(\d+~)?\d+\/courses\\?/], function () {
        if (!window.location.href.match(/gghhlearn.cisconetspace.com/) || !isAdminOrTeacher) {
            return $('.add_course_link').remove();
        }
    });

    mask.add('Account settings form fields', [/accounts\/((\d+~)?\d+|self)\/settings/], function () {
        var $form;
        $form = $('#account_settings');
        $form.find('#account_settings_open_registration,' +
                    '#account_settings_users_can_edit_name,' +
                    '#account_services_avatars').parent().hide();
        $form.find('#account_settings_self_enrollment').parent().parent().hide();
        $form.find('.account_domains').hide();
        $form.find('#account_settings_teachers_can_create_courses').parents('fieldset:first').hide();
        return $form.find('#account_name').prop('disabled', true);
    });

    mask.add('Users, quotas, and tools tabs', [/accounts\/(\d+~)?\d+\/settings/], function () {
        $('#tab-users-link, #tab-tools-link, #tab-quotas-link').parent().remove();
        return $('#tab-users, #tab-tools, #tab-quotas').remove();
    });

    mask.add('Manage profile pictures link', [/accounts\/(\d+~)?\d+\/users$/], function () {
        return $('#right-side .manage_profile_pictures').remove();
    });

    mask.add('remove delete from link', [/accounts\/(\d+~)?\d+\/users/], function () {
        return $('td.links a[href$="delete"]').remove();
    });

    mask.add('Edit profile button', [/profile/, /about\/(\d+~)?\d+$/], function () {
        return $('a.edit_profile_link').remove();
    });

    mask.add('Edit settings button', [/profile/, /about\/(\d+~)?\d+$/], function () {
        return $('a.edit_settings_link').remove();
    });

    mask.add('Ways to log in table', [/profile/, /about\/(\d+~)?\d+$/], function () {
        return $('table.summary.pseudonym_list').parent().remove();
    });

    mask.add('Birth date', [/profile/, /about\/(\d+~)?\d+$/], function () {
        return $('label[for="user_birthdate"]').parent().parent().remove();
    });

    mask.add('Reset course content button', [/courses\/(\d+~)?\d+\/(settings|details)/], function () {
        return $('a.reset_course_content_button').remove();
    });

    mask.add('User profile membership information', [/courses\/(\d+~)?\d+\/users\/(\d+~)?\d+$/], function () {
        return $('.more_user_information fieldset:first-child tr:last-child').remove();
    });

    mask.add('Disable course detail form elements', [/courses\/(\d+~)?\d+\/(settings|details)/], function () {
        $('#course_name').prop('disabled', true);
        $('#course_course_code').prop('disabled', true);
        $('#course_sis_source_id').prop('disabled', true);
        $('#course_account_id').prop('disabled', true);
        $('#course_start_at').prop('disabled', true);
        $('.input-append button.ui-datepicker-trigger').prop('disabled', true);
        $('.input-append button.ui-datepicker-trigger').prop('disabled', true);
        $('#course_conclude_at').prop('disabled', true);
        $('#course_restrict_enrollments_to_course_dates').prop('disabled', true);
        return $('body').one('click', '#course_form', function () {
            return $(this).find('.ui-datepicker-trigger').remove();
        });
    });

    mask.add('Use communication channel as pseudonym option', [/profile$/, /about\/(\d+~)?\d+$/], function () {
        return $('#build_pseudonym_for_email').parent().append('&nbsp;').children().hide();
    });

    mask.add('Gradebook add students button', [/gradebook/], function () {
        return $('.add_students').remove();
    });

    mask.add('Delete enrollment links', [/courses\/(\d+~)?\d+\/users\/(\d+~)?\d+$/], function () {
        $('a.delete_enrollment_link').remove();
        return $('a.delete_enrollment_link').parent().remove();
    });

    mask.add('Course license <select> tag', [/courses\/(\d+~)?\d+\/(settings|details)$/], function () {
        $('#course_license').prop('disabled', true);
        return $('.license_help_link').remove();
    });

    mask.add('Course user types', [/courses\/(\d+~)?\d+\/(settings|details)$/], function () {
        $('#observer_enrollments').parent().remove();
        $('#designer_enrollments').parent().remove();
        $('#ta_enrollments').parent().remove();
        $('.observer_count').parent().remove();
        $('.designer_count').parent().remove();
        return $('.ta_count').parent().remove();
    });

    //mask.add('Delete User Breadcrumb Navigation on Files Page', [/files/], function () {
    //    return $('#breadcrumbs').remove();
    //});

    mask.add('Designer, TA, and observer enrollment lists', [/courses\/(\d+~)?\d+\/(settings|details)/], function () {
        return $('#designer_enrollments, #ta_enrollments, #observer_enrollments').parent().remove();
    });

    mask.add('User groups', [/courses\/(\d+~)?\d+\/groups/], function () {
        return $('a:contains("Add Students to the Course")').remove();
    });

    mask.add('Course-Level permissions', [/accounts\/((\d+~)?\d+|self)\/permissions$/], function () {
        return $('td[data-permission_name="manage_admin_users"],' +
                 'td[data-permission_name="manage_students"],' +
                 'td[data-permission_name="manage_user_logins"],' +
                 'td[data-permission_name="manage_frozen_assignments"],' +
                 'td[data-permission_name="manage_courses"]').parent().remove();
    });

    mask.add('Delete enrollment links', [/courses\/(\d+~)?\d+\/users/], function () {
        this.afterLoad('.student_roster .sections', function (e) {
            return e.remove();
        });
        return this.afterLoad('.teacher_roster .sections', function (e) {
            return e.remove();
        });
    });
    /* Causing UI issues
    mask.add('Hide section column on people table', [/courses\/(\d+~)?\d+\/users/], function () {
        var hide;
        hide = function () {
            if (($('table.roster tr')).length > 0) {
                return $('table.roster tr').each(function () {
                    return $(this).children().filter(':nth-child(4)').remove();
                });
            } else {
                return setTimeout(function () {
                    return hide();
                }, 100);
            }
        };
        return hide();
    });*/
    
    mask.add('Hide enrollments in dropdown', [/courses\/(\d+~)?\d+\/users/], function () {
        var hide, item, items, _i, _len, _results;
        items = ['TaEnrollment', 'DesignerEnrollment', 'ObserverEnrollment'];
        hide = function (item) {
            if ($("select[name=enrollment_role] option[value='" + item + "']").length > 0) {
                return $("select[name=enrollment_role] option[value='" + item + "']").remove();
            } else {
                return setTimeout(function () {
                    return hide(item);
                }, 100);
            }
        };
        _results = [];
        for (_i = 0, _len = items.length; _i < _len; _i++) {
            item = items[_i];
            _results.push(hide(item));
        }
        return _results;
    });
    /* Deprecated
    mask.add('Hide Add People button', [/courses\/(\d+~)?\d+\/users$/], function () {
        if (!window.location.href.match(/gghhlearn.cisconetspace.com/) || !isAdminOrTeacher) {
            var count_incr, cur_count, hideLink, max_count;
            max_count = 100 * 10 * 10;
            cur_count = 0;
            count_incr = 100;
            hideLink = function () {
                cur_count += count_incr;
                if ($('#addUsers').length > 0) {
                    return $('#addUsers').remove();
                } else if ($('.form-inline a.btn.pull-right.icon-add').length > 0) {
                    return $('.form-inline a.btn.pull-right.icon-add').remove();
                } else {
                    if (cur_count < max_count) {
                        return setTimeout(function () {
                            return hideLink();
                        }, 100);
                    }
                }
            };
            return hideLink();
        }
    });
    */
    //Hides Add People except for the GGHH account in Prod
    mask.add('Hide Add People button', [/courses\/(\d+~)?\d+\/users$/], function () {
        if (!window.location.href.match(/gghhlearn.cisconetspace.com/) || !isAdminOrTeacher) {
            hideLink = function () {
                if ($('#addUsers').length > 0) {
                    return $('#addUsers').remove();
                }
                else {
                    return setTimeout(function () {
                        return hideLink();
                    }, 100);
                }
            };
            return hideLink();
        }
    });

    mask.add('Course section', [/courses\/(\d+~)?\d+\/sections\/(\d+~)?\d+$/], function () {
        $('.crosslist_link').remove();
        return $('.edit_section_link').remove();
    });

    mask.add('Course right navigation', [/courses\/(\d+~)?\d+\/(settings|details)/], function () {
        return $('.copy_course_link').remove();
    });

    mask.add('Course right navigation', [/courses\/(\d+~)?\d+\/settings/], function () {
        return $('#course_storage_quota_mb').attr("disabled", true);
    });

    mask.add('Account Permissions Add Role Button', [/accounts\/(\d+~)?\d+\/permissions/], function () {
        $('div.new-role').remove();
        $('#account_roles td[data-permission_name="manage_courses"]').parent().remove();
        $('#account_roles td[data-permission_name="manage_user_logins"]').parent().remove();
        $('#account_roles td[data-permission_name="manage_students"]').parent().remove();
        $('#account_roles td[data-permission_name="manage_frozen_assignments"]').parent().remove();
        $('#account_roles td[data-permission_name="manage_admin_users"]').parent().remove();
        $('#course_roles td[data-permission_name="manage_admin_users"]').parent().remove();
        $('#course_roles td[data-permission_name="manage_sections"]').parent().remove();
        return $('#course_roles tr').each(function () {
            $(this).children().filter(':nth-child(3)').remove();
            $(this).children().filter(':nth-child(4)').remove();
            return $(this).children().filter(':nth-child(4)').remove();
        });
    });

    mask.add('courses right navigation', [/courses\/(\d+~)?\d+\/(details|settings)/], function () {
        return $('table.summary').find("tr:gt(2)").remove();
    });
	
	/*----------------------------------
       01/29/2018
       WEF = World Economic Forum 
       Courses are linked from EdCast platform.
       Do not apply regular overrides to WEF courses.
       Only apply IoE() function.
    ----------------------------------*/
    var wefAcademy = false;
	if (window.location.href.match(/568933118.netacad.com/)) {
	wefAcademy = true;
	console.log(window.location.href + ": WEF Academy Detected");
    }

    $(document).ready(function () {
		
		if($.cookie('liferay-referrer') === undefined) {
			$.cookie('liferay-referrer', document.referrer.split('/')[2]);
		}

		if (wefAcademy == false) {
		
			console.log('Applying UI mask');
			mask.hideUI();

			console.log('Applying custom overrides');
			processCustoms().init();
		} else {
			console.log("Not applying UI Masks and custom overrides for WEF Academy");
		}

        console.log('Checking for IoE');
        if (window.location.href.match(/gghhlearn.cisconetspace.com/)) {
            $('#global_nav_help_link').hide(); //hiding help link for gghh.
        }
        if (window.location.href.match(/lmstest-gghh.canvas.cisco.instructure.com/)) {
            $('#global_nav_help_link').hide(); //hiding help link for gghh test.
        }
        if (window.location.href.match(/learn-test.ciscoskillzone.cisco.instructure.com/)) {
            $('#global_nav_help_link').hide(); //hiding help link for skillzone test.
        }
        if (window.location.href.match(/lms-ciscoskillzone.netacad.com/)) {
            $('#global_nav_help_link').hide(); //hiding help link for skillzone.
        }
        var course_id;
        var context = (typeof window.ENV.context_asset_string == 'string') && window.ENV.context_asset_string.split('_');
        if ((context instanceof Array) && context.length > 1) {
            course_id = context[0] == 'course' && context[1];
        }

        //if (window.location.href.match(/lms-ciscoskillzone.netacad.com/)) {
        //    $("ul#identity li:nth-child(3)").hide(); //hiding settings link
        //    $("ul#identity li:nth-last-child(1)").hide(); // Hide Help Link. Achyutha - 10/14/2015
        //    $('#header-logo-secondary').text('SkillZone');
        //}

        if (course_id) {
            console.log('Course context detected');
            IoE(course_id);
        }

		if (wefAcademy == false) {
			
			if (window.location.href.match(/login/)) {
				logo = $('<h1>', {
					"class": 'cisco-landing-logo'
				});

				$('#modal-box').append(logo);
			}

			//Global Nav Sorting
			
			//Moves "My Netacad" to the top of the menu
			$('#menu li:last').remove().prependTo("#menu");
			
			var pageTitle = $('h1.page-title').text();
			$('h1.page-title').prop('title', pageTitle).addClass('ellipsis');
		}
    });
});
