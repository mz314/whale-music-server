<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0"
                xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
    <xsl:template match="/response/content">
        <html>
            <body>
                <ul>
                    
                    <xsl:for-each select="directory/item"> 
                        <li> 
                        <xsl:choose>
                            <xsl:when test="file=0"> 
                                <a href="?command=listdir&amp;dir={path}">
                                    <xsl:value-of select="path"/>
                                </a>
                            </xsl:when>
                            <xsl:otherwise>
                                <a href="?command=playfile&amp;file={path}"><xsl:value-of select="path" /></a>
                            </xsl:otherwise>
                        </xsl:choose>
                        </li>
                    </xsl:for-each>

                </ul>
            </body>
        </html>
    </xsl:template>
</xsl:stylesheet>