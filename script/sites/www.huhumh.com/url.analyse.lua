------------------------------------------------------------
---http://www.huhumh.com/
------------------------------------------------------------
function Analyse(url)
    local page_type = GetPageType(url)
    if type(page_type) ~= "string" then
        return nil, "GetPageType failed for url:" .. url
    end
    -- guess the type of page
    if "comic" == page_type then
        return ComicUrlAnalyse(url, pagestr, "")
    end
    if "volume" == page_type then
        return VolumeUrlAnalyse(url, pagestr, "")
    end
    if "picture" == page_type then
        return PictureUrlAnalyse(url, pagestr, "")
    end
    return nil, "Unknown page type:" .. page_type .. " for url:" .. url
end
------------------------------------------------------------
site_mode = ".huhumh.com" -- .XXX.com
site_chinese_name = "��������" --XXXXX
site_thread_count = 100 -- 1~100
site_resource_CD  = 0 -- second
site_host = "http://www.huhumh.com/" --http://www.XXX.com/
------------------------------------------------------------
function GetPageType(url)
    -- comic   page URL sample: http://www.huhumh.com/manhua/hu97/
    -- volume  page URL sample: http://www.huhumh.com/mh/hu97/199573.htm?s=4
    -- picture page URL sample: http://www.huhumh.com/mh/hu97/199573.htm?s=4*v=1
    local last_slash_index = JumpStr(url, 1, '/', 4)
    if type(last_slash_index) ~= "number" then
        return nil
    end

    if last_slash_index == string.len(url) + 1 then
        return "comic"
    end
    
    local bar_index = JumpStr(url, last_slash_index, "-", 1)
    -- no bar('-') means volume page
    if type(bar_index) ~= "number" then
        return "volume"
    end

    return "picture"
end
