<?xml version="1.0" encoding="UTF-8"?>

<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<xsl:template match="/">


<html>
	<head>
		<script>
			function addDisplay (details) {
			document.write(details);
		}
		</script>
	</head>  
	<body>
		<table border="1">
			<tbody>
				<!--First table row for titles-->
				<tr>
					<th>Course No.</th>
					<th>Course Title</th>
					<th>Prof</th>
					<th>Year</th>
					<th>Days</th>
					<th>Time</th>
					<th>Location</th>
				</tr>
				<!--Loop through each course in input-->
				<xsl:for-each select="courses/course">
					<!--Check to make sure course year is >= 2003-->
					<xsl:if test="@acad_year &gt; 2002">
					<tr>
						<!--Displaying course num, and if theris multiple with ", "-->
						<td>
							<xsl:for-each select="course_num">
								<xsl:value-of select="current()"/>
								<!--If it is not the last course num add ", "-->
								<xsl:if test="position()!=last()">
									<p style="display:inline">, </p>
								</xsl:if>
							</xsl:for-each>
						</td>
						<!--Display as <a href> element for link description-->
						<td>
							<xsl:element name="a">
								<xsl variable name="desc">
									<xsl:value-of select="description"/>
								</xsl:variable>
								<xsl:attribute name="href">
									<xsl:value-of select="JavaScript:addDisplay($details)"/>
								<xsl:value-of select="title"/>
							</xsl:element>
						</td>
						<!--Displaying multiple profs if needed-->
						<td>
							<xsl:for-each select="course_head/person">
								<xsl:value-of select="person_name"/>
								<!--If it is not the last prof add ", "-->
								<xsl:if test="position()!=last()">
									<p style="display:inline">, </p>
								</xsl:if>
							</xsl:for-each>
						</td>
						<!--Display year-location-->
						<td><xsl:value-of select="@acad_year"/></td>
						<td><xsl:value-of select="meeting/meeting_days"/></td>
						<td>
							<xsl:value-of select="meeting/meeting_begin"/>
							<p style="display:inline"> - </p>
							<xsl:value-of select="meeting/meeting_end"/>
						</td>
						<td><xsl:value-of select="meeting/location"/></td>
					</tr>
					</xsl:if>
				</xsl:for-each>
			</tbody>
		</table>
	</body>
</html>


</xsl:template>

</xsl:stylesheet> 